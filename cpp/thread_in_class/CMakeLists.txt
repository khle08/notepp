cmake_minimum_required(VERSION 3.21)
project(structure_test)

set(CMAKE_CXX_STANDARD 14)

add_executable(class_with_thread main.cpp class_with_thread/class_with_thread.cpp)
