#pragma once

#include <optional>
#include "Models/EncodedVideoFrame.h"
#include "Models/VideoFrame.h"

namespace tanaka {

enum class VideoCodec : std::uint8_t { Raw, H264, H265, VP9 };

class IVideoEncoder {
 public:
  virtual ~IVideoEncoder() = default;
  IVideoEncoder(const IVideoEncoder&) = default;
  auto operator=(const IVideoEncoder&) -> IVideoEncoder& = default;
  IVideoEncoder(IVideoEncoder&&) = default;
  auto operator=(IVideoEncoder&&) -> IVideoEncoder& = default;

  [[nodiscard]] virtual auto Encode(VideoFrame&& frame) const
      -> std::optional<EncodedVideoFrame> = 0;
  [[nodiscard]] virtual auto Codec() const -> VideoCodec = 0;

 protected:
  IVideoEncoder() = default;
};

}  // namespace tanaka
