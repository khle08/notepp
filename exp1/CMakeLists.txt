cmake_minimum_required(VERSION 3.10)
project(MyProject VERSION 1.0.0)

find_package(Eigen3 REQUIRED)
message("[!!!] Eigen3 DIR: ${EIGEN3_INCLUDE_DIR}")

set(MY_VARIABLE "i am a variable")
message(STATUS "the variable value is: ${MY_VARIABLE}")
