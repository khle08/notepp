
cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project("expMqtt" LANGUAGES C CXX VERSION 1.0.0)


# cmakelists 设置c++11 
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Setup where the compiled libraries will be installed
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)


########################################################################
# [!] Setup where Paho is compiled
# set(paho_dir /home/ubt/Documents/library/paho.mqtt.c/ubuntu)
set(paho_dir ${CMAKE_CURRENT_SOURCE_DIR}/lib/paho)

if (APPLE)
    file(GLOB PAHO_LIBS ${paho_dir}/lib/*.dylib)
elseif (WIN32)
    file(GLOB PAHO_LIBS ${paho_dir}/lib/*.dll)
else()
    file(GLOB PAHO_LIBS ${paho_dir}/lib/*.so)
endif()

include_directories(${paho_dir}/include)
link_directories(${paho_dir}/lib)
########################################################################


# If this (below) is defined in lib/CMakeLists.txt, exe will not know how to include
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_subdirectory(lib)


find_package(Threads REQUIRED)

list(APPEND SOURCE
    main.cpp
)

add_executable(exe ${SOURCE})

target_link_libraries(exe PRIVATE 
                      ${CMAKE_THREAD_LIBS_INIT}
                      ${PAHO_LIBS}
                      # pahoMqtt  # Failed to compile this way (err: -lpahoMqtt not found)
                      mqtt
                      )
