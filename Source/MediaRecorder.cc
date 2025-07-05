#include "MediaRecorder.h"

namespace tanaka {

MediaRecorder::MediaRecorder(VideoPipeline VideoPipeline)
    : videoPipeline_(std::move(VideoPipeline)) {}

auto MediaRecorder::StartRecording() -> bool {
  if (recordingThread_.joinable()) {
    return false;
  }

  recordingThread_ = std::jthread([this](const std::stop_token& token) {
    while (!token.stop_requested()) {
      constexpr int sleepDuration = 33;
      std::this_thread::sleep_for(std::chrono::milliseconds(sleepDuration));

      if (auto videoFrame = videoPipeline_.Source().CaptureFrame()) {
        for (const auto& processor : videoPipeline_.Processors()) {
          videoFrame = processor->Process(std::move(*videoFrame));
        }
        if (auto encoded =
                videoPipeline_.Encoder().Encode(std::move(*videoFrame))) {
          // todo muxer_->AddVideoFrame(*encoded);
        }
      }

      // todo audioFrame
    }

    // todo finalize mux
    // todo write to ioutput
  });

  return true;
}

auto MediaRecorder::StopRecording() -> void {
  recordingThread_.request_stop();
}

}  // namespace tanaka
