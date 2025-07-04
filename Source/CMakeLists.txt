include(${CMAKE_SOURCE_DIR}/Cmake/SetTargetDefaults.cmake)

set(TANAKA_SOURCES)

if(WIN32)
    list(APPEND TANAKA_SOURCES VideoSources/WgcVideoSource.cc)
endif()

add_library(tanaka ${TANAKA_SOURCES})

set_target_defaults(tanaka)

target_include_directories(tanaka PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)
