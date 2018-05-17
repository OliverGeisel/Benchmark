cmake_minimum_required(VERSION 3.10)
project(Benchmark C)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-march=native -O3")

set(CMAKE_C_STANDARD 99)
add_executable(Benchmark src/main.c src/matrix/matrixArray.c src/matrix/matrixArray.h src/matrix/matrixPointer.c src/matrix/matrixPointer.h)