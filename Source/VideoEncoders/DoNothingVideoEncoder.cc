#include "DoNothingVideoEncoder.h"

namespace tanaka {

// NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
auto DoNothingVideoEncoder::Encode(VideoFrame&& frame) const
    -> std::optional<EncodedVideoFrame> {
  return {{frame.Pixels(), frame.Timestamp()}};
}

}  // namespace tanaka
