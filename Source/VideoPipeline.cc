#include "VideoPipeline.h"

namespace tanaka {

VideoPipeline::VideoPipeline(std::unique_ptr<IVideoFrameSource> source,
                             std::unique_ptr<IVideoProcessor> processor)
    : source_(std::move(source)), processor_(std::move(processor)) {}

auto VideoPipeline::GetNextFrame() -> std::optional<VideoFrame> {
  if (auto frame = source_->CaptureFrame()) {
    frame = processor_->ProcessFrame(std::move(*frame));
    // todo encoding
    return frame;
  }

  return std::nullopt;
}

}  // namespace tanaka
