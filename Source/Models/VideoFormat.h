#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace tanaka {

enum class PixelFormat : std::uint8_t {
  BGRA,
  RGBA,
};

class VideoFormat {
 public:
  // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
  VideoFormat(size_t width, size_t height, PixelFormat format)
      : width_(width), height_(height), format_(format) {}

  [[nodiscard]] auto Width() const -> size_t { return width_; }
  [[nodiscard]] auto Height() const -> size_t { return height_; }
  [[nodiscard]] auto Format() const -> PixelFormat { return format_; }

  [[nodiscard]] auto BytesPerPixel() const -> size_t {
    switch (format_) {
      case PixelFormat::BGRA:
      case PixelFormat::RGBA:
        return 4;
      default:
        throw std::runtime_error("Unsupported pixel format");
    }
  }

  [[nodiscard]] auto TotalBytes() const -> size_t {
    switch (format_) {
      case PixelFormat::BGRA:
      case PixelFormat::RGBA:
        return width_ * height_ * 4;
      default:
        throw std::runtime_error("Unsupported pixel format");
    }
  }

  [[nodiscard]] auto BitRate(int fps) const -> int64_t {
    constexpr int bitsPerByte = 8;
    return static_cast<int64_t>(TotalBytes()) * fps * bitsPerByte;
  }

 private:
  size_t width_;
  size_t height_;
  PixelFormat format_;
};

}  // namespace tanaka
