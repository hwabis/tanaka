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
          videoFrame = processor->ProcessFrame(std::move(*videoFrame));
        }
        // todo encode
      }

      // todo audioFrame
      // todo mux, support output interfaces
    }

    // todo finalize encoder, output once more?
  });

  return true;
}

auto MediaRecorder::StopRecording() -> void {
  recordingThread_.request_stop();
}

}  // namespace tanaka
