cmake_minimum_required(VERSION 3.0.0)
project(ipow VERSION 0.1.0)

set(CMAKE_BUILD_TYPE RELEASE)

add_executable(ipow_benchmark benchmark.cpp)
target_compile_features(ipow_benchmark PRIVATE cxx_std_17)
target_compile_options(ipow_benchmark PRIVATE "-Wall;-Wextra;-pedantic;-ffast-math;-march=native")

add_executable(ipow_test test.cpp)
target_compile_features(ipow_test PRIVATE cxx_std_20)
target_compile_options(ipow_test PRIVATE "-Wall;-Wextra;-pedantic")
