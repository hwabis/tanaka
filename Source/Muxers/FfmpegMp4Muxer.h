#pragma once

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
}

#include <vector>
#include "IMuxer.h"
#include "Models/VideoFormat.h"
#include "VideoEncoders/IVideoEncoder.h"

namespace tanaka {

class FfmpegMp4Muxer : public IMuxer {
 public:
  FfmpegMp4Muxer(const VideoFormat& format, int fps, VideoCodec videoCodec);

  ~FfmpegMp4Muxer() override;
  FfmpegMp4Muxer(const FfmpegMp4Muxer&) = delete;
  auto operator=(const FfmpegMp4Muxer&) -> FfmpegMp4Muxer& = delete;
  FfmpegMp4Muxer(FfmpegMp4Muxer&&) = delete;
  auto operator=(FfmpegMp4Muxer&&) -> FfmpegMp4Muxer& = delete;

  auto AddVideoFrame(const EncodedVideoFrame& frame) -> void override;
  [[nodiscard]] auto Finalize() -> std::vector<std::byte> override;

 private:
  auto initializeFormat() -> void;
  auto writeHeader() -> void;
  auto writeTrailer() -> void;
  static auto writePacket(void* opaque, const uint8_t* buf, int bufSize) -> int;
  static auto seek(void* opaque, int64_t offset, int whence) -> int64_t;

  AVFormatContext* formatContext_ = nullptr;
  AVStream* videoStream_ = nullptr;
  AVIOContext* ioContext_ = nullptr;

  std::vector<std::byte> outputBuffer_;
  VideoFormat format_;
  int fps_;
  VideoCodec videoCodec_;
  int64_t frameCount_ = 0;
  bool headerWritten_ = false;
  bool finalized_ = false;
};

}  // namespace tanaka
