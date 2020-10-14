cmake_minimum_required(VERSION 3.14)

include(FetchContent)

FetchContent_Declare(
    googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
)
FetchContent_GetProperties(googlebenchmark)
if(NOT googlebenchmark_POPULATED)
  FetchContent_Populate(googlebenchmark)
  set(BENCHMARK_ENABLE_TESTING off)
  add_subdirectory(${googlebenchmark_SOURCE_DIR} ${googlebenchmark_BINARY_DIR})
endif()

add_executable(ipow_benchmark benchmark.cpp)
target_compile_features(ipow_benchmark PRIVATE cxx_std_20)
target_compile_options(ipow_benchmark PRIVATE "-Wall;-Wextra;-pedantic")
target_link_libraries(ipow_benchmark PRIVATE ipow::ipow benchmark)
