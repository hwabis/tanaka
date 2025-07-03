cmake_minimum_required(VERSION 3.31)

project(
  Tanaka
  LANGUAGES CXX
)

enable_testing()

find_package(GTest 1.17 REQUIRED)

add_subdirectory(Source)
add_subdirectory(Tests)
