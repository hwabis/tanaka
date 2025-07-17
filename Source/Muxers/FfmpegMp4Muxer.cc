#include "FfmpegMp4Muxer.h"
#include <cstring>
#include <stdexcept>

namespace tanaka {

FfmpegMp4Muxer::FfmpegMp4Muxer(const VideoFormat& format,
                               int fps,
                               VideoCodec videoCodec)
    : format_(format), fps_(fps), videoCodec_(videoCodec) {
  initializeFormat();
}

FfmpegMp4Muxer::~FfmpegMp4Muxer() {
  if (ioContext_ != nullptr) {
    av_freep(static_cast<void*>(&ioContext_->buffer));
    avio_context_free(&ioContext_);
  }
  if (formatContext_ != nullptr) {
    avformat_free_context(formatContext_);
  }
}

auto FfmpegMp4Muxer::initializeFormat() -> void {
  if (avformat_alloc_output_context2(&formatContext_, nullptr, "avi", nullptr) <
      0) {
    throw std::runtime_error("Failed to allocate output format context");
  }

  videoStream_ = avformat_new_stream(formatContext_, nullptr);
  if (videoStream_ == nullptr) {
    throw std::runtime_error("Failed to create video stream");
  }

  auto* codecpar = videoStream_->codecpar;
  codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
  switch (videoCodec_) {
    case VideoCodec::Raw:
      codecpar->codec_id = AV_CODEC_ID_RAWVIDEO;
      codecpar->format = AV_PIX_FMT_BGRA;
      // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      codecpar->bits_per_coded_sample = 32;
      // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      codecpar->bits_per_raw_sample = 8;
      codecpar->codec_tag = 0;
      break;
    case VideoCodec::H264:
      codecpar->codec_id = AV_CODEC_ID_H264;
      codecpar->format = AV_PIX_FMT_YUV420P;
      break;
    case VideoCodec::H265:
      codecpar->codec_id = AV_CODEC_ID_HEVC;
      codecpar->format = AV_PIX_FMT_YUV420P;
      break;
    case VideoCodec::VP9:
      codecpar->codec_id = AV_CODEC_ID_VP9;
      codecpar->format = AV_PIX_FMT_YUV420P;
      break;
    default:
      throw std::runtime_error("Unsupported video codec");
  }
  codecpar->width = static_cast<int>(format_.Width());
  codecpar->height = static_cast<int>(format_.Height());

  videoStream_->time_base = {.num = 1, .den = fps_};

  constexpr size_t bufferSize = 65536;
  auto* buffer = static_cast<uint8_t*>(av_malloc(bufferSize));
  if (buffer == nullptr) {
    throw std::runtime_error("Failed to allocate IO buffer");
  }

  ioContext_ =
      avio_alloc_context(buffer, bufferSize, 1, &outputBuffer_, nullptr,
                         FfmpegMp4Muxer::writePacket, FfmpegMp4Muxer::seek);
  if (ioContext_ == nullptr) {
    av_free(buffer);
    throw std::runtime_error("Failed to allocate IO context");
  }

  formatContext_->pb = ioContext_;
}

auto FfmpegMp4Muxer::writeHeader() -> void {
  if (headerWritten_) {
    return;
  }

  if (avformat_write_header(formatContext_, nullptr) < 0) {
    throw std::runtime_error("Failed to write format header");
  }

  headerWritten_ = true;
}

auto FfmpegMp4Muxer::AddVideoFrame(const EncodedVideoFrame& frame) -> void {
  if (finalized_) {
    throw std::runtime_error("Cannot add frames after finalization");
  }

  if (!headerWritten_) {
    writeHeader();
  }

  AVPacket* packet = av_packet_alloc();
  if (packet == nullptr) {
    throw std::runtime_error("Failed to allocate packet");
  }

  auto frameData = frame.Data();
  packet->size = static_cast<int>(frameData.size());
  packet->data = static_cast<uint8_t*>(av_malloc(packet->size));
  if (packet->data == nullptr) {
    av_packet_free(&packet);
    throw std::runtime_error("Failed to allocate packet data");
  }
  std::memcpy(packet->data, frameData.data(), packet->size);
  packet->buf = av_buffer_create(packet->data, packet->size,
                                 av_buffer_default_free, nullptr, 0);

  constexpr int64_t usPerSec = 1000000;
  packet->pts =
      av_rescale_q(frame.Timestamp(), {1, usPerSec}, videoStream_->time_base);
  packet->dts = packet->pts;
  // NOLINTNEXTLINE(hicpp-signed-bitwise)
  packet->flags |= AV_PKT_FLAG_KEY;

  if (av_interleaved_write_frame(formatContext_, packet) < 0) {
    av_packet_free(&packet);
    throw std::runtime_error("Failed to write video frame");
  }

  av_packet_free(&packet);
  frameCount_++;
}

auto FfmpegMp4Muxer::writeTrailer() -> void {
  if (av_write_trailer(formatContext_) < 0) {
    throw std::runtime_error("Failed to write format trailer");
  }
}

auto FfmpegMp4Muxer::Finalize() -> std::vector<std::byte> {
  if (finalized_) {
    return outputBuffer_;
  }

  if (!headerWritten_) {
    writeHeader();
  }

  writeTrailer();

  if (ioContext_ != nullptr) {
    avio_flush(ioContext_);
  }

  finalized_ = true;
  return outputBuffer_;
}

auto FfmpegMp4Muxer::writePacket(void* opaque, const uint8_t* buf, int bufSize)
    -> int {
  auto* buffer = static_cast<std::vector<std::byte>*>(opaque);

  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  auto bufSpan = std::span{reinterpret_cast<const std::byte*>(buf),
                           static_cast<size_t>(bufSize)};
  buffer->insert(buffer->end(), bufSpan.begin(), bufSpan.end());

  return bufSize;
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
auto FfmpegMp4Muxer::seek(void* opaque, int64_t offset, int whence) -> int64_t {
  // todo this is all fake or smth
  auto* buffer = static_cast<std::vector<std::byte>*>(opaque);

  if (whence == SEEK_CUR) {
    return static_cast<int64_t>(buffer->size());
  }
  if (whence == SEEK_END) {
    return static_cast<int64_t>(buffer->size());
  }
  if (whence == SEEK_SET) {
    return offset;
  }

  return -1;
}

}  // namespace tanaka
