#ifdef _WIN32

#pragma once

#include "IVideoFrameSource.h"
#include "VideoFrame.h"

#include <windows.h>
#include <winrt/windows.graphics.capture.h>

namespace tanaka {

class WgcVideoSource : public IVideoFrameSource {
 public:
  WgcVideoSource();
  auto captureFrame() -> VideoFrame override;
  auto hasMoreFrames() -> bool override;

 private:
  winrt::Windows::Graphics::Capture::GraphicsCaptureItem captureItem = nullptr;
};

}  // namespace tanaka

#endif
