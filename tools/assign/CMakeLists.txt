cmake_minimum_required(VERSION "3.10.0")

project(assign VERSION 1.0.0)

# cmakelists 设置c++11 
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()


add_subdirectory(lib)


# Define where to start "#include" XX.h and XX.cpp files to the code
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/lib)
link_directories(${PROJECT_BINARY_DIR}/lib)


add_executable(exe main.cpp)
target_link_libraries(exe PRIVATE munkres)
