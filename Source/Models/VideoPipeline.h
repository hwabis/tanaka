#pragma once

#include <memory>
#include <vector>
#include "VideoEncoders/IVideoEncoder.h"
#include "VideoProcessors/IVideoProcessor.h"
#include "VideoSources/IVideoSource.h"

namespace tanaka {

class VideoPipeline {
 public:
  VideoPipeline(std::unique_ptr<IVideoSource> source,
                std::vector<std::unique_ptr<IVideoProcessor>> processors,
                std::unique_ptr<IVideoEncoder> encoder)
      : source_(std::move(source)),
        processors_(std::move(processors)),
        encoder_(std::move(encoder)) {}

  [[nodiscard]] auto Source() const -> const IVideoSource& { return *source_; }
  [[nodiscard]] auto Processors() const
      -> const std::vector<std::unique_ptr<IVideoProcessor>>& {
    return processors_;
  }
  [[nodiscard]] auto Encoder() const -> const IVideoEncoder& {
    return *encoder_;
  }

 private:
  std::unique_ptr<IVideoSource> source_;
  std::vector<std::unique_ptr<IVideoProcessor>> processors_;
  std::unique_ptr<IVideoEncoder> encoder_;
};

}  // namespace tanaka
