#include "DoNothingVideoProcessor.h"

namespace tanaka {

auto DoNothingVideoProcessor::Process(VideoFrame&& frame) -> VideoFrame {
  return std::move(frame);
}

}  // namespace tanaka
