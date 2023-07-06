cmake_minimum_required(VERSION "3.10.0")

project(justAName VERSION 1.0.0)


# cmakelists 设置c++11 
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()

# Set up required headers
include_directories(daemon/include)

add_library(name hello.hpp hello.cpp daemon/source/daemon.cpp)
add_executable(exeName main.cpp)

target_link_libraries(exeName PRIVATE name)


# Install the config file
install(FILES daemon/resource/config/daemon-template.conf 
        DESTINATION /etc/daemon-template)

# Intall the systemd file
install(FILES daemon/resource/systemd/exeName.service 
        DESTINATION /etc/systemd/system)

# Install the binary program
install(TARGETS exeName DESTINATION /usr/bin)