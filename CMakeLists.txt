cmake_minimum_required(VERSION 3.31)

project(
  Tanaka
  LANGUAGES CXX
)

enable_testing()
find_package(GTest 1.17 REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FFMPEG REQUIRED IMPORTED_TARGET
  libavformat
  libavcodec
  libavutil
)

add_subdirectory(Source)
add_subdirectory(Tests)
