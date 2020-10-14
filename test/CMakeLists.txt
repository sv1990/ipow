cmake_minimum_required(VERSION 3.14)

add_executable(ipow_test test.cpp)
target_compile_features(ipow_test PRIVATE cxx_std_20)
target_compile_options(ipow_test PRIVATE "-Wall;-Wextra;-pedantic")
target_link_libraries(ipow_test PRIVATE ipow::ipow)
