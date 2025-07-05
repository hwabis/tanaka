#pragma once

#include <memory>
#include "VideoPipeline.h"

namespace tanaka {

// todo support audio pipeline as well
class MediaRecorder {
 public:
  MediaRecorder(std::unique_ptr<VideoPipeline> videoPipeline);

  auto StartRecording() -> void;
  auto StopRecording() -> void;

 private:
  std::unique_ptr<VideoPipeline> videoPipeline_;
  bool recording_ = false;
};

}  // namespace tanaka
