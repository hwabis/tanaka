#include "WgcVideoSource.h"

namespace tanaka {

auto WgcVideoSource::captureFrame() -> VideoFrame {
  return {};
}

auto WgcVideoSource::hasMoreFrames() -> bool {
  return true;
}

}  // namespace tanaka
