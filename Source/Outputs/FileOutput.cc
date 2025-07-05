#include "FileOutput.h"

namespace tanaka {

auto FileOutput::Write(std::span<const std::byte> data) -> void {
  file_.write(reinterpret_cast<const char*>(data.data()),
              static_cast<std::streamsize>(data.size()));
}

auto FileOutput::Close() -> void {
  file_.close();
}

}  // namespace tanaka
