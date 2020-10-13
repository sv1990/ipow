cmake_minimum_required(VERSION 3.0.0)
project(ipow VERSION 0.1.0)

set(CMAKE_BUILD_TYPE RELEASE)

add_library(ipow INTERFACE)
add_library(ipow::ipow ALIAS ipow)
target_include_directories(ipow INTERFACE include)

add_subdirectory(test)
add_subdirectory(benchmark)