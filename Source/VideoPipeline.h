#pragma once

#include <memory>
#include <optional>
#include "VideoProcessors/IVideoProcessor.h"
#include "VideoSources/IVideoFrameSource.h"

namespace tanaka {

class VideoPipeline {
 public:
  VideoPipeline(std::unique_ptr<IVideoFrameSource> source,
                std::unique_ptr<IVideoProcessor> processor);

  auto GetNextFrame() -> std::optional<VideoFrame>;

 private:
  std::unique_ptr<IVideoFrameSource> source_;
  std::unique_ptr<IVideoProcessor> processor_;
};

}  // namespace tanaka
