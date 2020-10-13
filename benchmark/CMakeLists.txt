cmake_minimum_required(VERSION 3.0.0)

add_executable(ipow_benchmark benchmark.cpp)
target_compile_features(ipow_benchmark PRIVATE cxx_std_20)
target_compile_options(ipow_benchmark PRIVATE "-Wall;-Wextra;-pedantic")
target_link_libraries(ipow_benchmark PRIVATE ipow::ipow)