#include "MediaRecorder.h"

namespace tanaka {

MediaRecorder::MediaRecorder(MediaSettings mediaSettings)
    : settings_(std::move(mediaSettings)) {}

auto MediaRecorder::StartRecording() -> bool {
  if (recordingThread_.joinable()) {
    return false;
  }

  // todo streaming and stuff isn't possible like this since we have to wait for
  // stop token or source to run out of frames before any output happens LOL
  recordingThread_ = std::jthread([this](const std::stop_token& token) {
    // todo also check if audio has more frames? idk
    while (!token.stop_requested() &&
           settings_.GetVideoPipeline().Source().HasMoreFrames()) {
      constexpr int sleepDuration = 33;
      std::this_thread::sleep_for(std::chrono::milliseconds(sleepDuration));

      const auto& videoPipeline = settings_.GetVideoPipeline();

      if (auto videoFrame = videoPipeline.Source().CaptureFrame()) {
        for (const auto& processor : videoPipeline.Processors()) {
          videoFrame = processor->Process(std::move(*videoFrame));
        }
        if (auto encoded =
                videoPipeline.Encoder().Encode(std::move(*videoFrame))) {
          settings_.GetMuxer().AddVideoFrame(*encoded);
        }
      }

      // todo audioFrame
    }

    auto data = settings_.GetMuxer().Finalize();
    settings_.GetOutput().Write(data);
  });

  return true;
}

auto MediaRecorder::StopRecording() -> void {
  recordingThread_.request_stop();
}

}  // namespace tanaka
