include(${CMAKE_SOURCE_DIR}/Cmake/SetTargetDefaults.cmake)

add_library(tanaka
  lolol.cc
)

set_target_defaults(tanaka)

target_include_directories(tanaka PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)
