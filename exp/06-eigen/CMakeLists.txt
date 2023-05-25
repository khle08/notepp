
cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project("expEigen" LANGUAGES C CXX VERSION 1.0.0)


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


set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)


set(EIGEN_LIB_DIR "/Users/kcl/Documents/Cpp_Projects/notepp/library")

file(GLOB Eigen_directory_files "${EIGEN_LIB_DIR}/Eigen/*")

foreach(f ${Eigen_directory_files})
    if(NOT f MATCHES "\\.txt" AND NOT f MATCHES "${ESCAPED_CMAKE_CURRENT_SOURCE_DIR}/[.].+" AND NOT f MATCHES "${ESCAPED_CMAKE_CURRENT_SOURCE_DIR}/src")
        list(APPEND Eigen_directory_files_to_install ${f})
    endif()
endforeach(f ${Eigen_directory_files})

# install(FILES ${Eigen_directory_files_to_install}
#         DESTINATION lib/Eigen COMPONENT Devel)

# Define where to start "#include" XX.h and XX.cpp files from the library, i.e., Eigen
include_directories(BEFORE ${EIGEN_LIB_DIR})
link_directories(${EIGEN_LIB_DIR})


# If this (below) is defined in lib/CMakeLists.txt, exe will not know how to include
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_subdirectory(lib)


find_package(Threads REQUIRED)

list(APPEND SOURCE
    main.cpp
)

add_executable(expEigen ${SOURCE})

target_link_libraries(expEigen PRIVATE 
                      ${CMAKE_THREAD_LIBS_INIT}
                      # assign
                      testlibs
                      )
