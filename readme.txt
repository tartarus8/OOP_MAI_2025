CMake building:
mkdir -p build && cd build
cmake ..

Base testing:
ctest --output-on-failure
cmake --fresh .. && ctest --output-on-failure


Bruteforce testing:
cmake --build . --target task1_tests
./task_1/task1_tests

Base compilation:
g++ ./task_1/src/task_1.cpp -o main
./main
