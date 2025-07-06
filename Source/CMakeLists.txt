include(${CMAKE_SOURCE_DIR}/Cmake/SetTargetDefaults.cmake)

add_library(tanaka
  Outputs/FileOutput.cc
  VideoEncoders/DoNothingVideoEncoder.cc
  VideoProcessors/DoNothingVideoProcessor.cc
  VideoSources/WgcVideoSource.cc
  Muxers/FfmpegMp4Muxer.cc
  MediaRecorder.cc
)

set_target_defaults(tanaka)

target_include_directories(tanaka PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(tanaka PRIVATE
  PkgConfig::FFMPEG
)

if(WIN32)
  target_link_libraries(tanaka PRIVATE windowsapp)
endif()
