#pragma once

#include <cstddef>
#include <span>
#include <vector>

namespace tanaka {

class EncodedVideoFrame {
 public:
  EncodedVideoFrame(std::span<const std::byte> buffer, int64_t timestampUs)
      : data_(buffer.begin(), buffer.end()), timestampUs_(timestampUs) {}

  [[nodiscard]] auto Size() const -> size_t { return data_.size(); }
  [[nodiscard]] auto Data() const -> std::span<const std::byte> {
    return data_;
  }
  [[nodiscard]] auto Timestamp() const -> int64_t { return timestampUs_; }

 private:
  std::vector<std::byte> data_;
  int64_t timestampUs_;
};

}  // namespace tanaka
