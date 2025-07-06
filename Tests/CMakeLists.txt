include(${CMAKE_SOURCE_DIR}/Cmake/AddTestExecutable.cmake)

add_test_executable(tanaka-tests tanaka
  VideoSources/TestWgcVideoSource.cc
  TestMediaRecorder.cc
)
