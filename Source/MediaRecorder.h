#pragma once

#include <thread>
#include "Models/MediaSettings.h"

namespace tanaka {

class MediaRecorder {
 public:
  explicit MediaRecorder(MediaSettings mediaSettings);

  ~MediaRecorder();

  MediaRecorder(const MediaRecorder&) = delete;
  auto operator=(const MediaRecorder&) -> MediaRecorder& = delete;
  MediaRecorder(MediaRecorder&&) = delete;
  auto operator=(MediaRecorder&&) -> MediaRecorder& = delete;

  auto StartRecording() -> bool;
  auto StopRecording() -> void;

 private:
  // Goes first so the dtor destroys this before other members
  std::jthread recordingThread_;
  MediaSettings settings_;
};

}  // namespace tanaka
