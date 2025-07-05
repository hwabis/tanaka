#include "DoNothingVideoProcessor.h"

namespace tanaka {

auto DoNothingVideoProcessor::ProcessFrame(VideoFrame&& frame) -> VideoFrame {
  return std::move(frame);
}

}  // namespace tanaka
