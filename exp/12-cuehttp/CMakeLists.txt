
cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project("expcuehttp" LANGUAGES C CXX VERSION 1.0.0)


# cmakelists 设置c++11 
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wno-error=deprecated-declarations -Wno-deprecated-declarations")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++17 support. Please use a different C++ compiler.")
endif()

# Setup where the compiled libraries will be installed
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)


########################################################################
option(ENABLE_HTTPS "enable https" ON)

# [!] Setup where cuehttp header files are located
set(cuehttp_dir ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include_directories(${cuehttp_dir}/include)
include_directories(${cuehttp_dir}/include/cuehttp/deps)
include_directories(${cuehttp_dir}/include/cuehttp/deps/asio)
########################################################################


# If this (below) is defined in lib/CMakeLists.txt, exe will not know how to include
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_subdirectory(lib)

find_package(Threads REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})


if (ENABLE_HTTPS)
    message("-- enable https")
    find_package(OpenSSL REQUIRED)
    include_directories(${OPENSSL_INCLUDE_DIR})
    add_definitions(-DENABLE_HTTPS)
endif ()


list(APPEND SOURCE
    main.cpp
    # example.cpp
)

add_executable(exe ${SOURCE})

target_link_libraries(exe PRIVATE 
                      ${CMAKE_THREAD_LIBS_INIT}
                      ${Boost_LIBRARIES}
                      )

if (ENABLE_HTTPS)
    target_link_libraries(exe PRIVATE ${OPENSSL_LIBRARIES})
endif ()
