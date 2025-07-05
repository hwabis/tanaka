#pragma once

#include "IVideoProcessor.h"

namespace tanaka {

class DoNothingVideoProcessor : public IVideoProcessor {
 public:
  auto ProcessFrame(VideoFrame&& frame) -> VideoFrame override;
};

}  // namespace tanaka
