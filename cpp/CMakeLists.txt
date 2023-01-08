# This CMakeList file supports the testing on windows with Clion
cmake_minimum_required(VERSION 3.21)
project(cpp_test)


add_executable(encode encode.cpp)
add_executable(errors errors.cpp)


#include_directories( ./jsonTest/dist/)
#add_executable(JsonTest ./jsonTest/Json_io.cpp ./jsonTest/dist/jsoncpp.cpp)