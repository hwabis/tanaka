#pragma once

#include <optional>
#include "VideoFrame.h"

namespace tanaka {

class IVideoFrameSource {
 public:
  virtual ~IVideoFrameSource() = default;
  IVideoFrameSource(const IVideoFrameSource&) = delete;
  auto operator=(const IVideoFrameSource&) -> IVideoFrameSource& = delete;
  IVideoFrameSource(IVideoFrameSource&&) = delete;
  auto operator=(IVideoFrameSource&&) -> IVideoFrameSource& = delete;

  virtual auto CaptureFrame() -> std::optional<VideoFrame> = 0;
  virtual auto HasMoreFrames() -> bool = 0;

 protected:
  IVideoFrameSource() = default;
};

}  // namespace tanaka
