#pragma once

#include <optional>
#include "IVideoEncoder.h"
#include "Models/EncodedVideoFrame.h"
#include "Models/VideoFrame.h"

namespace tanaka {

class DoNothingVideoEncoder : public IVideoEncoder {
 public:
  [[nodiscard]] auto Encode(VideoFrame&& frame) const
      -> std::optional<EncodedVideoFrame> override;
  [[nodiscard]] auto Codec() const -> VideoCodec override;
};

}  // namespace tanaka
