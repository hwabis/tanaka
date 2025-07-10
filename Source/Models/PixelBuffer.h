#pragma once

#include <cstddef>
#include <span>
#include <vector>

namespace tanaka {
class PixelBuffer {
 public:
  // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
  PixelBuffer(size_t width, size_t height) : width_(width), height_(height) {}

  [[nodiscard]] auto Data() -> std::span<std::byte> { return data_; }
  [[nodiscard]] auto Data() const -> std::span<const std::byte> {
    return data_;
  }
  [[nodiscard]] auto Width() const -> size_t { return width_; }
  [[nodiscard]] auto Height() const -> size_t { return height_; }
  [[nodiscard]] auto Bitrate(int fps) const -> int64_t {
    constexpr int BITS_PER_BYTE = 8;
    return static_cast<int64_t>(data_.size()) * fps * BITS_PER_BYTE;
  }

  // todo
  // auto SetPixel(size_t x, size_t y, Color color) -> void;
  // auto GetPixel(size_t x, size_t y) const -> Color;

 private:
  size_t width_;
  size_t height_;
  std::vector<std::byte> data_;
};

}  // namespace tanaka
