include(${CMAKE_SOURCE_DIR}/Cmake/SetTargetDefaults.cmake)

add_library(tanaka
  VideoEncoders/DoNothingVideoEncoder.cc
  VideoProcessors/DoNothingVideoProcessor.cc
  VideoSources/WgcVideoSource.cc
  MediaRecorder.cc
)

set_target_defaults(tanaka)

target_include_directories(tanaka PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

if(WIN32)
  target_link_libraries(tanaka PRIVATE windowsapp)
endif()
