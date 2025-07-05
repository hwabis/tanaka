#pragma once

#include "Outputs/IOutput.h"
#include "VideoPipeline.h"

namespace tanaka {

class MediaSettings {
 public:
  MediaSettings(VideoPipeline videoPipeline, std::unique_ptr<IOutput> output)
      : videoPipeline_(std::move(videoPipeline)), output_(std::move(output)) {}

  [[nodiscard]] auto GetVideoPipeline() const -> const VideoPipeline& {
    return videoPipeline_;
  }
  [[nodiscard]] auto GetOutput() const -> const IOutput& { return *output_; }

 private:
  VideoPipeline videoPipeline_;
  // todo AudioPipeline audioPipeline_;
  // todo std::unique_ptr<IMuxer> muxer_;
  std::unique_ptr<IOutput> output_;
};

}  // namespace tanaka
