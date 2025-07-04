#pragma once

#include "VideoFrame.h"

namespace tanaka {

class IVideoFrameSource {
 public:
  virtual ~IVideoFrameSource() = default;
  IVideoFrameSource(const IVideoFrameSource&) = delete;
  auto operator=(const IVideoFrameSource&) -> IVideoFrameSource& = delete;
  IVideoFrameSource(IVideoFrameSource&&) = delete;
  auto operator=(IVideoFrameSource&&) -> IVideoFrameSource& = delete;

  virtual auto captureFrame() -> VideoFrame = 0;
  virtual auto hasMoreFrames() -> bool = 0;
};

}  // namespace tanaka
