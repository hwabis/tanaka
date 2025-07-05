#pragma once

#include <optional>
#include "Models/VideoFrame.h"

namespace tanaka {

class IVideoSource {
 public:
  virtual ~IVideoSource() = default;
  IVideoSource(const IVideoSource&) = delete;
  auto operator=(const IVideoSource&) -> IVideoSource& = delete;
  IVideoSource(IVideoSource&&) = delete;
  auto operator=(IVideoSource&&) -> IVideoSource& = delete;

  virtual auto CaptureFrame() -> std::optional<VideoFrame> = 0;
  virtual auto HasMoreFrames() -> bool = 0;

 protected:
  IVideoSource() = default;
};

}  // namespace tanaka
