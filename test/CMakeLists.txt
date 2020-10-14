cmake_minimum_required(VERSION 3.14)

include(FetchContent)

FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/onqtam/doctest.git
)
FetchContent_GetProperties(doctest)
if(NOT doctest_POPULATED)
  FetchContent_Populate(doctest)
  set(DOCTEST_WITH_TESTS off)
  add_subdirectory(${doctest_SOURCE_DIR} ${doctest_BINARY_DIR})
endif()

add_executable(ipow_test test.cpp)
add_test(ipow_test ipow_test)
target_compile_features(ipow_test PRIVATE cxx_std_20)
target_compile_options(ipow_test PRIVATE "-Wall;-Wextra;-pedantic")
target_link_libraries(ipow_test PRIVATE ipow::ipow doctest::doctest)
