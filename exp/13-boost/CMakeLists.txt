
cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project("expBoost" LANGUAGES C CXX VERSION 1.0.0)


# cmakelists 设置c++17
set(CMAKE_CXX_STANDARD 17)

# Setup where the compiled libraries will be installed
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)


find_package(Threads REQUIRED)

find_package(Boost REQUIRED COMPONENTS system filesystem)

# [!] If package is found, the following settings would not be necessary
# include_directories(BEFORE /usr/include)
# link_directories(/usr/lib)

# If this (below) is defined in lib/CMakeLists.txt, exe will not know how to include
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_subdirectory(lib)

list(APPEND SOURCE
    main.cpp
)

add_executable(exe ${SOURCE})

target_link_libraries(exe PRIVATE
                      ${CMAKE_THREAD_LIBS_INIT}
                      HttpServer
                      Boost::system
                      Boost::filesystem
                      )
