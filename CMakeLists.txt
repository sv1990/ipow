cmake_minimum_required(VERSION 3.0.0)
project(ipow VERSION 0.1.0)

set(CMAKE_BUILD_TYPE RELEASE)

add_executable(ipow main.cpp)
target_compile_features(ipow PRIVATE cxx_std_20)
target_compile_options(ipow PRIVATE "-Wall;-Wextra;-pedantic")
