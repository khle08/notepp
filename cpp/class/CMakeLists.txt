cmake_minimum_required(VERSION "3.13.0")

project(landowner VERSION 1.0.0)

add_library(owner class.h class.cpp)
add_executable(game main.cpp)

target_link_libraries(game PRIVATE owner)
