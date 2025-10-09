cmake_minimum_required(VERSION 3.16)

add_library(task2_lib
    src/array.cpp
    src/eleven.cpp
)
target_include_directories(task2_lib PUBLIC include)

add_executable(task2_app src/main.cpp)
target_link_libraries(task2_app PRIVATE task2_lib)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(INSTALL_GTEST OFF CACHE BOOL "Disable gtest install" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(task2_tests tests/tests.cpp)
target_link_libraries(task2_tests PRIVATE task2_lib gtest gtest_main)

include(GoogleTest)
set(CMAKE_GTEST_DISCOVER_TESTS_DISCOVERY_MODE PRE_TEST)
gtest_discover_tests(task2_tests
  DISCOVERY_TIMEOUT 30
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
