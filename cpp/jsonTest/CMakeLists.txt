cmake_minimum_required(VERSION 3.21)
project(JsonTest)

set(CMAKE_CXX_STANDARD 14)


# the folder “dist” is a created library by a python project on github : https://github.com/open-source-parsers/jsoncpp .
include_directories( ./dist/)


add_executable(JsonTest Json_io.cpp ./dist/jsoncpp.cpp)
add_executable(JsonTest2 Json_io2.cpp ./dist/jsoncpp.cpp)
