#pragma once

#include <cstddef>
#include <span>

namespace tanaka {

class IOutput {
 public:
  virtual ~IOutput() = default;
  IOutput(const IOutput&) = default;
  auto operator=(const IOutput&) -> IOutput& = default;
  IOutput(IOutput&&) = default;
  auto operator=(IOutput&&) -> IOutput& = default;

  virtual auto Write(std::span<const std::byte> data) -> void = 0;
  virtual auto Close() -> void = 0;

 protected:
  IOutput() = default;
};

}  // namespace tanaka
