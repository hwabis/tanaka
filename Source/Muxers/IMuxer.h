#pragma once

#include <cstddef>
#include <vector>
#include "Models/EncodedVideoFrame.h"

namespace tanaka {

class IMuxer {
 public:
  virtual ~IMuxer() = default;
  IMuxer(const IMuxer&) = default;
  auto operator=(const IMuxer&) -> IMuxer& = default;
  IMuxer(IMuxer&&) = default;
  auto operator=(IMuxer&&) -> IMuxer& = default;

  virtual auto AddVideoFrame(const EncodedVideoFrame& frame) -> void = 0;
  // todo addaudioframe
  [[nodiscard]] virtual auto Finalize() -> std::vector<std::byte> = 0;

 protected:
  IMuxer() = default;
};

}  // namespace tanaka
