#pragma once

#include <thread>
#include "Models/VideoPipeline.h"

namespace tanaka {

class MediaRecorder {
 public:
  MediaRecorder(VideoPipeline VideoPipeline);

  auto StartRecording() -> bool;
  auto StopRecording() -> void;

 private:
  // Goes first so the dtor destroys this before other members
  std::jthread recordingThread_;

  VideoPipeline videoPipeline_;
  // todo audio
};

}  // namespace tanaka
