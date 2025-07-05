#include "MediaRecorder.h"

namespace tanaka {

MediaRecorder::MediaRecorder(VideoPipeline VideoPipeline)
    : videoPipeline_(std::move(VideoPipeline)) {}

auto MediaRecorder::StartRecording() -> bool {
  if (recordingThread_.joinable()) {
    return false;
  }

  // todo streaming and stuff isn't possible like this since we have to wait for
  // stop token or source to run out of frames before any output happens LOL
  recordingThread_ = std::jthread([this](const std::stop_token& token) {
    while (!token.stop_requested() && videoPipeline_.Source().HasMoreFrames()) {
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
    // videoPipeline_.Output().Write(muxer_->GetData());
  });

  return true;
}

auto MediaRecorder::StopRecording() -> void {
  recordingThread_.request_stop();
}

}  // namespace tanaka
