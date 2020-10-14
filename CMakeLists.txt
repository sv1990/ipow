cmake_minimum_required(VERSION 3.14)
project(ipow VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE RELEASE)

add_library(ipow INTERFACE)
add_library(ipow::ipow ALIAS ipow)
target_include_directories(ipow INTERFACE include)

add_subdirectory(benchmark)
enable_testing()
add_subdirectory(test)