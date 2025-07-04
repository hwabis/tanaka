#include <gtest/gtest.h>

#include <VideoSources/WgcVideoSource.h>

TEST(WgcVideoSource, CanCaptureFrame) {
  tanaka::WgcVideoSource source;
  auto frame = source.CaptureFrame();
  EXPECT_GT(frame.Width, 0);
  EXPECT_GT(frame.Height, 0);
  EXPECT_FALSE(frame.Pixels.empty());
}
