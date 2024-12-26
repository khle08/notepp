
cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project("expOpenCV" LANGUAGES C CXX VERSION 1.0.0)


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

# Setup where the compiled libraries will be installed
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

# ======================================================================

set(CMAKE_INSTALL_RPATH $ORIGIN/lib)
set(SDK_DIR /home/kcl/Documents/tools/Sophon-SDK-24.04.01/sophon-img_20240624_155933/soc-sdk)

include_directories(${SDK_DIR}/include)
link_directories(${SDK_DIR}/lib)

file(GLOB OpenCV_LIBS ${SDK_DIR}/lib/*.so)
file(GLOB FFMPEG_LIBS ${SDK_DIR}/lib/*.a)

include_directories(${SDK_DIR}/include/opencv4)

# ======================================================================

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
                      imgReader
                      ${FFMPEG_LIBS}
                      ${OpenCV_LIBS}
                      )
