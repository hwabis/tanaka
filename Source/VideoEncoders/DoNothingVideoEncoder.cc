#include "DoNothingVideoEncoder.h"

namespace tanaka {

auto DoNothingVideoEncoder::Encode(VideoFrame&& frame) const
    -> std::optional<EncodedVideoFrame> {
  return {{frame.Pixels(), frame.Timestamp()}};
}

}  // namespace tanaka
