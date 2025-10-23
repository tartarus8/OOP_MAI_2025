cmake_minimum_required(VERSION 3.16)
project(course_tasks LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")

include(CTest)  # or: enable_testing()

add_subdirectory(task_2)
