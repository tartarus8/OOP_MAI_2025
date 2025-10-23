How to build:
Check for neccessary subdirectories in core CMakeLists.txt, then:
cmake -S . -B build
cmake --build build
ctest --test-dir build
