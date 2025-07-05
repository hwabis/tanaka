#include <gtest/gtest.h>

#include <VideoSources/WgcVideoSource.h>

TEST(WgcVideoSource, CanCaptureFrame) {
  tanaka::WgcVideoSource source;
  auto frame = source.CaptureFrame();

  std::cout << "Captured frame: " << frame.Width() << "x" << frame.Height()
            << ", first pixel: " << static_cast<int>(frame.Pixels()[0]) << "\n";
}
