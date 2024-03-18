cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project("expJson" LANGUAGES C CXX VERSION 1.0.0)


set(CMAKE_CXX_STANDARD 11)

# the folder “dist” is a created library by a python project on github : https://github.com/open-source-parsers/jsoncpp .
include_directories(${CMAKE_SOURCE_DIR}/dist)


add_executable(expJson main.cpp ${CMAKE_SOURCE_DIR}/dist/jsoncpp.cpp)
add_executable(expJson2 main2.cpp ${CMAKE_SOURCE_DIR}/dist/jsoncpp.cpp)
