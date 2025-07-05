#pragma once

#include "VideoSources/VideoFrame.h"

namespace tanaka {

class IVideoProcessor {
 public:
  virtual ~IVideoProcessor() = default;
  IVideoProcessor(const IVideoProcessor&) = default;
  auto operator=(const IVideoProcessor&) -> IVideoProcessor& = default;
  IVideoProcessor(IVideoProcessor&&) = default;
  auto operator=(IVideoProcessor&&) -> IVideoProcessor& = default;

  virtual auto ProcessFrame(VideoFrame&& frame) -> VideoFrame = 0;

 protected:
  IVideoProcessor() = default;
};

}  // namespace tanaka
