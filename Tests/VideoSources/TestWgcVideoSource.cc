#include <VideoSources/WgcVideoSource.h>
#include <gtest/gtest.h>
#include <chrono>
#include <optional>
#include <thread>

TEST(WgcVideoSource, CanCaptureFrame) {
  tanaka::WgcVideoSource source;

  // Give WGC time to start capturing, then try to get a frame
  constexpr int sleepTime = 100;
  std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));

  auto frameOpt = source.CaptureFrame();
  ASSERT_TRUE(frameOpt.has_value());
  auto& frame = frameOpt.value();
  auto pixels = frame.Pixels();
  bool hasData = false;
  for (auto& pixel : pixels) {
    if (pixel != std::byte{0}) {
      hasData = true;
      break;
    }
  }

  EXPECT_GT(frame.Width(), 0);
  EXPECT_GT(frame.Height(), 0);
  EXPECT_TRUE(hasData) << "Frame should contain actual pixel data";
}
