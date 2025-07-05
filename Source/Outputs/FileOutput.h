#pragma once

#include <fstream>
#include "IOutput.h"

namespace tanaka {

class FileOutput : public IOutput {
 public:
  explicit FileOutput(const std::string& path)
      : file_(path, std::ios::binary) {}

  auto Write(std::span<const std::byte> data) -> void override;
  auto Close() -> void override;

 private:
  std::ofstream file_;
};

}  // namespace tanaka
