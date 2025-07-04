#ifdef _WIN32

#include "WgcVideoSource.h"

namespace tanaka {

WgcVideoSource::WgcVideoSource() {
  winrt::init_apartment();
  auto interop = winrt::get_activation_factory<
                     winrt::Windows::Graphics::Capture::GraphicsCaptureItem>()
                     .as<IGraphicsCaptureItemInterop>();
  HMONITOR hMonitor = MonitorFromPoint({0, 0}, MONITOR_DEFAULTTOPRIMARY);
  winrt::com_ptr<winrt::Windows::Graphics::Capture::IGraphicsCaptureItem>
      itemPtr;
  winrt::check_hresult(interop->CreateForMonitor(
      hMonitor,
      winrt::guid_of<winrt::Windows::Graphics::Capture::IGraphicsCaptureItem>(),
      itemPtr.put_void()));
  captureItem_ =
      itemPtr.as<winrt::Windows::Graphics::Capture::GraphicsCaptureItem>();

  D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
                    D3D11_SDK_VERSION, d3dDevice_.put(), nullptr,
                    d3dContext_.put());
  framePool_ =
      winrt::Windows::Graphics::Capture::Direct3D11CaptureFramePool::Create(
          createDirect3DDevice(d3dDevice_.get()),
          winrt::Windows::Graphics::DirectX::DirectXPixelFormat::
              B8G8R8A8UIntNormalized,
          2, captureItem_.Size());
  session_ = framePool_.CreateCaptureSession(captureItem_);
  session_.StartCapture();
}

auto WgcVideoSource::CaptureFrame() -> VideoFrame {
  VideoFrame frame;

  auto captureFrame = framePool_.TryGetNextFrame();
  if (!captureFrame) {
    frame.Width = 1920;
    frame.Height = 1080;
    frame.Pixels.resize(1920 * 1080 * 4);
    return frame;
  }

  auto size = captureFrame.ContentSize();
  frame.Width = size.Width;
  frame.Height = size.Height;
  frame.Pixels.resize(size.Width * size.Height * 4);
  // todo

  return frame;
}

auto WgcVideoSource::HasMoreFrames() -> bool {
  return true;
}

auto WgcVideoSource::createDirect3DDevice(ID3D11Device* d3dDevice)
    -> winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice {
  winrt::com_ptr<IDXGIDevice> dxgiDevice;
  winrt::check_hresult(
      d3dDevice->QueryInterface(__uuidof(IDXGIDevice), dxgiDevice.put_void()));
  winrt::com_ptr<IInspectable> inspectable;
  winrt::check_hresult(CreateDirect3D11DeviceFromDXGIDevice(dxgiDevice.get(),
                                                            inspectable.put()));
  return inspectable
      .as<winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice>();
}

}  // namespace tanaka

#endif
