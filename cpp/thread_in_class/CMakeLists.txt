cmake_minimum_required(VERSION 3.21)
project(structure_test)

set(CMAKE_CXX_STANDARD 14)

add_executable(structure_test main.cpp)
add_executable(structure_test2 main2.cpp ./ob/test.cpp)
