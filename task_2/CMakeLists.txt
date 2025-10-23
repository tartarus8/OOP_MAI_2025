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

FetchContent_MakeAvailable(googletest)

add_library(mylib STATIC
  include/eleven.cpp
)

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

add_test(NAME MyProjectTests COMMAND tests)
