#ifdef _WIN32

#include "WgcVideoSource.h"

#include <windows.graphics.capture.interop.h>

namespace tanaka {

WgcVideoSource::WgcVideoSource() {
  winrt::init_apartment();

  auto interop = winrt::get_activation_factory<
                     winrt::Windows::Graphics::Capture::GraphicsCaptureItem>()
                     .as<IGraphicsCaptureItemInterop>();

  POINT pt = {0, 0};
  HMONITOR hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTOPRIMARY);

  winrt::com_ptr<winrt::Windows::Graphics::Capture::IGraphicsCaptureItem>
      itemPtr;
  winrt::check_hresult(interop->CreateForMonitor(
      hMonitor,
      winrt::guid_of<winrt::Windows::Graphics::Capture::IGraphicsCaptureItem>(),
      itemPtr.put_void()));

  captureItem =
      itemPtr.as<winrt::Windows::Graphics::Capture::GraphicsCaptureItem>();
}

auto WgcVideoSource::captureFrame() -> VideoFrame {
  VideoFrame frame;
  frame.Width = 1920;
  frame.Height = 1080;
  frame.Pixels.resize(1920 * 1080 * 4);
  return frame;
}

auto WgcVideoSource::hasMoreFrames() -> bool {
  return true;
}

}  // namespace tanaka

#endif
