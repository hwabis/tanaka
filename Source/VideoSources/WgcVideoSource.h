#pragma once

#include "IVideoFrameSource.h"
#include "VideoFrame.h"

namespace tanaka {

class WgcVideoSource : public IVideoFrameSource {
 public:
  auto captureFrame() -> VideoFrame override;
  auto hasMoreFrames() -> bool override;
};

}  // namespace tanaka
