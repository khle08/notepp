
cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project("expServer" LANGUAGES C CXX VERSION 1.0.0)


# cmakelists 设置c++17
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++17 support. Please use a different C++ compiler.")
endif()

# Setup where the compiled libraries will be installed
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)


find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)
# With ZLIB, use either ZLIB::ZLIB or z in "target_link_libraries" would be fine

add_subdirectory(lib)

include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

# [uSockets] Settings for the directory of uSockets library
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/lib/uSockets/src)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/uSockets/src)

# [uWebSockets] Settings for the directory of uWebSockets library
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/lib/uWebSockets/src)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/uWebSockets/src)


list(APPEND SOURCE
    main.cpp
)

add_executable(exe ${SOURCE})

target_link_libraries(exe PRIVATE 
                      ${CMAKE_THREAD_LIBS_INIT}
                      uSockets
                      z
                      -lstdc++fs
                      )
