#pragma once

#include <cstdint>
#include "VideoBuffer.h"
#include "VideoFormat.h"

namespace tanaka {

class VideoFrame {
 public:
  VideoFrame(const VideoFormat& format, int64_t timestampUs)
      : buffer_(format), timestampUs_(timestampUs) {}

  VideoFrame(const VideoFormat& format,
             std::span<const std::byte> data,
             int64_t timestampUs)
      : buffer_(format, data), timestampUs_(timestampUs) {}

  [[nodiscard]] auto Width() const -> size_t { return buffer_.Width(); }
  [[nodiscard]] auto Height() const -> size_t { return buffer_.Height(); }
  [[nodiscard]] auto Format() const -> const VideoFormat& {
    return buffer_.Format();
  }
  [[nodiscard]] auto Size() const -> size_t { return buffer_.Size(); }
  [[nodiscard]] auto Pixels() -> std::span<std::byte> { return buffer_.Data(); }
  [[nodiscard]] auto Pixels() const -> std::span<const std::byte> {
    return buffer_.Data();
  }
  [[nodiscard]] auto Timestamp() const -> int64_t { return timestampUs_; }
  [[nodiscard]] auto Buffer() const -> const VideoBuffer& { return buffer_; }

 private:
  VideoBuffer buffer_;
  int64_t timestampUs_;
};

}  // namespace tanaka
