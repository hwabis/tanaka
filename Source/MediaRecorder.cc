#include "MediaRecorder.h"
#include <thread>

namespace tanaka {

MediaRecorder::MediaRecorder(std::unique_ptr<VideoPipeline> videoPipeline)
    : videoPipeline_(std::move(videoPipeline)) {}

auto MediaRecorder::StartRecording() -> void {
  recordingThread_ = std::jthread([this](const std::stop_token& token) {
    while (!token.stop_requested()) {
      auto videoFrame = videoPipeline_->GetNextFrame();
      // todo output, support output interfaces

      constexpr int sleepDuration = 33;
      std::this_thread::sleep_for(std::chrono::milliseconds(sleepDuration));
    }
  });
}

auto MediaRecorder::StopRecording() -> void {
  recordingThread_.request_stop();
}

}  // namespace tanaka
