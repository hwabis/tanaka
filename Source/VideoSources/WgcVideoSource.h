#ifdef _WIN32

#pragma once

#include "IVideoFrameSource.h"
#include "VideoFrame.h"

#include <d3d11.h>
#include <dxgi1_2.h>
#include <windows.graphics.capture.interop.h>
#include <windows.graphics.directx.direct3d11.interop.h>
#include <windows.h>
#include <winrt/base.h>
#include <winrt/windows.graphics.capture.h>
#include <winrt/windows.graphics.directx.direct3d11.h>

namespace tanaka {

class WgcVideoSource : public IVideoFrameSource {
 public:
  WgcVideoSource();
  auto CaptureFrame() -> VideoFrame override;
  auto HasMoreFrames() -> bool override;

 private:
  static auto createDirect3DDevice(ID3D11Device* d3dDevice)
      -> winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice;

  winrt::Windows::Graphics::Capture::GraphicsCaptureItem captureItem_ = nullptr;
  winrt::com_ptr<ID3D11Device> d3dDevice_;
  winrt::com_ptr<ID3D11DeviceContext> d3dContext_;
  winrt::Windows::Graphics::Capture::Direct3D11CaptureFramePool framePool_ =
      nullptr;
  winrt::Windows::Graphics::Capture::GraphicsCaptureSession session_ = nullptr;
  winrt::com_ptr<ID3D11Texture2D> stagingTexture_;
};

}  // namespace tanaka

#endif
