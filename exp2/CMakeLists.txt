cmake_minimum_required(VERSION "3.13.0")

project(justAName VERSION 1.0.0)

add_library(lib-name hello.hpp hello.cpp)
add_executable(exeName main.cpp)

target_link_libraries(exeName PRIVATE lib-name)
