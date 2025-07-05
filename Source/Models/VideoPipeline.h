#pragma once

#include <memory>
#include <vector>
#include "Outputs/IOutput.h"
#include "VideoEncoders/IVideoEncoder.h"
#include "VideoProcessors/IVideoProcessor.h"
#include "VideoSources/IVideoSource.h"

namespace tanaka {

class VideoPipeline {
 public:
  VideoPipeline(std::unique_ptr<IVideoSource> source,
                std::vector<std::unique_ptr<IVideoProcessor>> processors,
                std::unique_ptr<IVideoEncoder> encoder,
                std::unique_ptr<IOutput> output)
      : source_(std::move(source)),
        processors_(std::move(processors)),
        encoder_(std::move(encoder)),
        output_(std::move(output)) {}

  [[nodiscard]] auto Source() const -> const IVideoSource& { return *source_; }
  [[nodiscard]] auto Processors() const
      -> const std::vector<std::unique_ptr<IVideoProcessor>>& {
    return processors_;
  }
  [[nodiscard]] auto Encoder() const -> const IVideoEncoder& {
    return *encoder_;
  }
  [[nodiscard]] auto Output() const -> const IOutput& { return *output_; }

 private:
  std::unique_ptr<IVideoSource> source_;
  std::vector<std::unique_ptr<IVideoProcessor>> processors_;
  std::unique_ptr<IVideoEncoder> encoder_;
  // todo this should live somewhere higher...
  std::unique_ptr<IOutput> output_;
};

}  // namespace tanaka
