#pragma once

#include <cstddef>
#include <vector>

namespace tanaka {

struct VideoFrame {
  std::vector<std::byte> Pixels;
  int Width;
  int Height;
};

}  // namespace tanaka
