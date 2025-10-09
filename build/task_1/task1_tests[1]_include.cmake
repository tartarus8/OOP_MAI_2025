if(EXISTS "/Users/tartarus/Documents/MAI/OOP_MAI_2025/build/task_1/task1_tests")
  if(NOT EXISTS "/Users/tartarus/Documents/MAI/OOP_MAI_2025/build/task_1/task1_tests[1]_tests.cmake" OR
     NOT "/Users/tartarus/Documents/MAI/OOP_MAI_2025/build/task_1/task1_tests[1]_tests.cmake" IS_NEWER_THAN "/Users/tartarus/Documents/MAI/OOP_MAI_2025/build/task_1/task1_tests" OR
     NOT "/Users/tartarus/Documents/MAI/OOP_MAI_2025/build/task_1/task1_tests[1]_tests.cmake" IS_NEWER_THAN "${CMAKE_CURRENT_LIST_FILE}")
    include("/opt/homebrew/share/cmake/Modules/GoogleTestAddTests.cmake")
    gtest_discover_tests_impl(
      TEST_EXECUTABLE [==[/Users/tartarus/Documents/MAI/OOP_MAI_2025/build/task_1/task1_tests]==]
      TEST_EXECUTOR [==[]==]
      TEST_WORKING_DIR [==[/Users/tartarus/Documents/MAI/OOP_MAI_2025/build/task_1]==]
      TEST_EXTRA_ARGS [==[]==]
      TEST_PROPERTIES [==[]==]
      TEST_PREFIX [==[]==]
      TEST_SUFFIX [==[]==]
      TEST_FILTER [==[]==]
      NO_PRETTY_TYPES [==[FALSE]==]
      NO_PRETTY_VALUES [==[FALSE]==]
      TEST_LIST [==[task1_tests_TESTS]==]
      CTEST_FILE [==[/Users/tartarus/Documents/MAI/OOP_MAI_2025/build/task_1/task1_tests[1]_tests.cmake]==]
      TEST_DISCOVERY_TIMEOUT [==[30]==]
      TEST_DISCOVERY_EXTRA_ARGS [==[]==]
      TEST_XML_OUTPUT_DIR [==[]==]
    )
  endif()
  include("/Users/tartarus/Documents/MAI/OOP_MAI_2025/build/task_1/task1_tests[1]_tests.cmake")
else()
  add_test(task1_tests_NOT_BUILT task1_tests_NOT_BUILT)
endif()
