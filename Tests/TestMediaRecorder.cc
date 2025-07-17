#include <gtest/gtest.h>
#include "MediaRecorder.h"
#include "Models/VideoFormat.h"
#include "Muxers/FfmpegMp4Muxer.h"
#include "Outputs/FileOutput.h"
#include "VideoEncoders/DoNothingVideoEncoder.h"
#include "VideoSources/WgcVideoSource.h"

namespace tanaka {

TEST(MediaRecorder, END_TO_END_LETS_GO) {
  auto source = std::make_unique<WgcVideoSource>();
  auto encoder = std::make_unique<DoNothingVideoEncoder>();
  VideoFormat format{1920, 1080, PixelFormat::BGRA};
  auto muxer = std::make_unique<FfmpegMp4Muxer>(format, 30, encoder->Codec());
  auto output = std::make_unique<FileOutput>("test.avi");

  auto recorder = MediaRecorder{{{std::move(source), {}, std::move(encoder)},
                                 std::move(muxer),
                                 std::move(output)}};
  recorder.StartRecording();
  std::this_thread::sleep_for(std::chrono::seconds(5));
  recorder.StopRecording();
}

}  // namespace tanaka
