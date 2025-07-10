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

  winrt::check_hresult(D3D11CreateDevice(
      nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
      D3D11_SDK_VERSION, d3dDevice_.put(), nullptr, d3dContext_.put()));
  framePool_ =
      winrt::Windows::Graphics::Capture::Direct3D11CaptureFramePool::Create(
          createDirect3DDevice(d3dDevice_.get()),
          winrt::Windows::Graphics::DirectX::DirectXPixelFormat::
              B8G8R8A8UIntNormalized,
          2, captureItem_.Size());

  D3D11_TEXTURE2D_DESC stagingDesc{
      .Width = static_cast<UINT>(captureItem_.Size().Width),
      .Height = static_cast<UINT>(captureItem_.Size().Height),
      .MipLevels = 1,
      .ArraySize = 1,
      .Format = DXGI_FORMAT_B8G8R8A8_UNORM,
      .Usage = D3D11_USAGE_STAGING,
      .BindFlags = 0,
      .CPUAccessFlags = D3D11_CPU_ACCESS_READ,
  };
  stagingDesc.SampleDesc.Count = 1;
  winrt::check_hresult(d3dDevice_->CreateTexture2D(&stagingDesc, nullptr,
                                                   stagingTexture_.put()));

  session_ = framePool_.CreateCaptureSession(captureItem_);
  session_.StartCapture();

  captureStartTime_ = std::chrono::steady_clock::now();
}

auto WgcVideoSource::CaptureFrame() const -> std::optional<VideoFrame> {
  winrt::Windows::Graphics::Capture::Direct3D11CaptureFrame frameToProcess =
      framePool_.TryGetNextFrame();
  if (!frameToProcess) {
    return std::nullopt;
  }

  auto size = frameToProcess.ContentSize();

  // todo cache this thing
  VideoFormat format{static_cast<size_t>(size.Width),
                     static_cast<size_t>(size.Height), PixelFormat::BGRA};
  VideoFrame frame{format, getCurrentTimestampUs()};

  auto surface = frameToProcess.Surface()
                     .as<winrt::Windows::Graphics::DirectX::Direct3D11::
                             IDirect3DSurface>();

  winrt::com_ptr<ID3D11Texture2D> d3dTexture;
  auto access = surface.as<
      Windows::Graphics::DirectX::Direct3D11::IDirect3DDxgiInterfaceAccess>();
  winrt::check_hresult(access->GetInterface(winrt::guid_of<ID3D11Texture2D>(),
                                            d3dTexture.put_void()));

  d3dContext_->CopyResource(stagingTexture_.get(), d3dTexture.get());
  D3D11_MAPPED_SUBRESOURCE mapped;
  winrt::check_hresult(
      d3dContext_->Map(stagingTexture_.get(), 0, D3D11_MAP_READ, 0, &mapped));

  auto pixels = frame.Pixels();
  std::memcpy(pixels.data(), mapped.pData, pixels.size());

  d3dContext_->Unmap(stagingTexture_.get(), 0);

  return frame;
}

auto WgcVideoSource::HasMoreFrames() const -> bool {
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

auto WgcVideoSource::getCurrentTimestampUs() const -> int64_t {
  auto now = std::chrono::steady_clock::now();
  auto elapsed = now - captureStartTime_;
  return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
};

}  // namespace tanaka

#endif
