#pragma once

#include <cstddef>
#include <span>
#include <vector>

namespace tanaka {

class EncodedVideoFrame {
 public:
  explicit EncodedVideoFrame(std::span<const std::byte> buffer)
      : data_(buffer.begin(), buffer.end()) {}

  [[nodiscard]] auto Size() const -> size_t { return data_.size(); }
  [[nodiscard]] auto Data() -> std::span<std::byte> { return data_; }
  [[nodiscard]] auto Data() const -> std::span<const std::byte> {
    return data_;
  }

 private:
  std::vector<std::byte> data_;
};

}  // namespace tanaka
