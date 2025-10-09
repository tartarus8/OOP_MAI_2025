cmake_minimum_required(VERSION 3.16)

add_executable(task1_app src/task_1.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(INSTALL_GTEST OFF CACHE BOOL "Disable gtest install" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(task1_tests tests/tests.cpp)
target_link_libraries(task1_tests PRIVATE gtest gtest_main)

include(GoogleTest)
set(CMAKE_GTEST_DISCOVER_TESTS_DISCOVERY_MODE PRE_TEST)
gtest_discover_tests(task1_tests
  DISCOVERY_TIMEOUT 30
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
