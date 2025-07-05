#pragma once

#include <memory>
#include <vector>
#include "VideoProcessors/IVideoProcessor.h"
#include "VideoSources/IVideoSource.h"

namespace tanaka {

class VideoPipeline {
 public:
  VideoPipeline(std::unique_ptr<IVideoSource> source,
                std::vector<std::unique_ptr<IVideoProcessor>> processors)
      : source_(std::move(source)), processors_(std::move(processors)) {}

  [[nodiscard]] auto Source() const -> IVideoSource& { return *source_; }
  [[nodiscard]] auto Processors() const
      -> const std::vector<std::unique_ptr<IVideoProcessor>>& {
    return processors_;
  }

 private:
  std::unique_ptr<IVideoSource> source_;
  std::vector<std::unique_ptr<IVideoProcessor>> processors_;
  // todo std::unique_ptr<IVideoEncoder> encoder;
};

}  // namespace tanaka
