cmake_minimum_required(VERSION 3.16)
project(task_2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
)
# Make the gtest targets (GTest::gtest, GTest::gtest_main, etc.) available
FetchContent_MakeAvailable(googletest)

add_library(mylib STATIC
  include/eleven.cpp
)
# If eleven.cpp includes headers like #include "eleven.hpp" from include/
target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()

add_executable(tests
  tests/tests.cpp
)
target_link_libraries(tests
  PRIVATE
    mylib
    GTest::gtest
)

# Either register the test binary directly...
add_test(NAME MyProjectTests COMMAND tests)

# ...or use gtest_discover_tests for automatic test discovery:
# include(GoogleTest)
# gtest_discover_tests(tests)
