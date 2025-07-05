#include "MediaRecorder.h"
#include <thread>

namespace tanaka {

MediaRecorder::MediaRecorder(std::unique_ptr<VideoPipeline> videoPipeline)
    : videoPipeline_(std::move(videoPipeline)) {}

auto MediaRecorder::StartRecording() -> void {
  recording_ = true;
  while (recording_) {
    auto videoFrame = videoPipeline_->GetNextFrame();
    // todo output, support output interfaces

    constexpr int sleepDuration = 33;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepDuration));
  }
}

auto MediaRecorder::StopRecording() -> void {
  recording_ = false;
}

}  // namespace tanaka
