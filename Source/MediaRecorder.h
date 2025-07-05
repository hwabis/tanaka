#pragma once

#include <memory>
#include <thread>
#include "VideoPipeline.h"

namespace tanaka {

// todo support audio pipeline as well
class MediaRecorder {
 public:
  MediaRecorder(std::unique_ptr<VideoPipeline> videoPipeline);

  auto StartRecording() -> void;
  auto StopRecording() -> void;

 private:
  // Goes first so the dtor destroys this before other members
  std::jthread recordingThread_;

  std::unique_ptr<VideoPipeline> videoPipeline_;
};

}  // namespace tanaka
