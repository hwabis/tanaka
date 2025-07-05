#pragma once

#include <optional>
#include "Models/EncodedVideoFrame.h"
#include "Models/VideoFrame.h"

namespace tanaka {

class IVideoEncoder {
 public:
  virtual ~IVideoEncoder() = default;
  IVideoEncoder(const IVideoEncoder&) = default;
  auto operator=(const IVideoEncoder&) -> IVideoEncoder& = default;
  IVideoEncoder(IVideoEncoder&&) = default;
  auto operator=(IVideoEncoder&&) -> IVideoEncoder& = default;

  virtual auto Encode(VideoFrame&& frame) const
      -> std::optional<EncodedVideoFrame> = 0;

 protected:
  IVideoEncoder() = default;
};

}  // namespace tanaka
