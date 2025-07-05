#pragma once

#include "Muxers/IMuxer.h"
#include "Outputs/IOutput.h"
#include "VideoPipeline.h"

namespace tanaka {

class MediaSettings {
 public:
  MediaSettings(VideoPipeline videoPipeline,
                std::unique_ptr<IMuxer> muxer,
                std::unique_ptr<IOutput> output)
      : videoPipeline_(std::move(videoPipeline)),
        muxer_(std::move(muxer)),
        output_(std::move(output)) {}

  [[nodiscard]] auto GetVideoPipeline() const -> const VideoPipeline& {
    return videoPipeline_;
  }
  [[nodiscard]] auto GetMuxer() -> IMuxer& { return *muxer_; }
  [[nodiscard]] auto GetOutput() -> IOutput& { return *output_; }

 private:
  VideoPipeline videoPipeline_;
  // todo AudioPipeline audioPipeline_;
  std::unique_ptr<IMuxer> muxer_;
  std::unique_ptr<IOutput> output_;
};

}  // namespace tanaka
