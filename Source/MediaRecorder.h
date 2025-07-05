#pragma once

#include <thread>
#include "Models/MediaSettings.h"

namespace tanaka {

class MediaRecorder {
 public:
  explicit MediaRecorder(MediaSettings mediaSettings);

  auto StartRecording() -> bool;
  auto StopRecording() -> void;

 private:
  // Goes first so the dtor destroys this before other members
  std::jthread recordingThread_;
  MediaSettings settings_;
};

}  // namespace tanaka
