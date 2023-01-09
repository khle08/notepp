# 建议新加的项目用独立文件夹分类，方便运行，方便管理
# 如果要用这个CMake 构建 cpp/根目录的 项目，需要编辑此CMakeLists文件, 通过add_executable 添加你想要的项目
# CMake 支持同时构建多个可执行文件的项目

# This CMakeList file supports the testing on windows with Clion to test the code in the /cpp/ root.
# Using g++ to build the executable target is also feasible.

cmake_minimum_required(VERSION 3.21)
project(cpp_test)


# 多个可执行文件的构建：
add_executable(encode encode.cpp)
add_executable(errors errors.cpp)
#include_directories( ./jsonTest/dist/)
#add_executable(JsonTest ./jsonTest/Json_io.cpp ./jsonTest/dist/jsoncpp.cpp)