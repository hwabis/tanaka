#pragma once

#include <algorithm>
#include <cstddef>
#include <span>
#include <vector>
#include "VideoFormat.h"

namespace tanaka {

class VideoBuffer {
 public:
  explicit VideoBuffer(const VideoFormat& format)
      : format_(format), data_(format.TotalBytes()) {}

  VideoBuffer(const VideoFormat& format, std::span<const std::byte> initialData)
      : format_(format), data_(initialData.begin(), initialData.end()) {
    if (data_.size() != format_.TotalBytes()) {
      data_.resize(format_.TotalBytes());
    }
  }

  [[nodiscard]] auto Format() const -> const VideoFormat& { return format_; }
  [[nodiscard]] auto Size() const -> size_t { return data_.size(); }
  [[nodiscard]] auto Data() -> std::span<std::byte> { return data_; }
  [[nodiscard]] auto Data() const -> std::span<const std::byte> {
    return data_;
  }

  [[nodiscard]] auto Width() const -> size_t { return format_.Width(); }
  [[nodiscard]] auto Height() const -> size_t { return format_.Height(); }

  auto Clear() -> void { std::ranges::fill(data_, std::byte{0}); }

  auto CopyFrom(std::span<const std::byte> source) -> void {
    const auto copySize = (std::min)(source.size(), data_.size());
    std::copy_n(source.begin(), copySize, data_.begin());
  }

 private:
  VideoFormat format_;
  std::vector<std::byte> data_;
};

}  // namespace tanaka
