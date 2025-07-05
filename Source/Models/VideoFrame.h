#pragma once

#include <cstddef>
#include <span>
#include <vector>

namespace tanaka {

class VideoFrame {
 public:
  VideoFrame(size_t width, size_t height)
      : width_(width), height_(height), pixels_(width * height * 4) {}

  [[nodiscard]] auto Width() const -> size_t { return width_; }
  [[nodiscard]] auto Height() const -> size_t { return height_; }
  [[nodiscard]] auto Size() const -> size_t { return pixels_.size(); }
  [[nodiscard]] auto Pixels() -> std::span<std::byte> { return pixels_; }
  [[nodiscard]] auto Pixels() const -> std::span<const std::byte> {
    return pixels_;
  }

 private:
  size_t width_;
  size_t height_;
  std::vector<std::byte> pixels_;
};

}  // namespace tanaka
