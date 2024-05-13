
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


# # Option 1. cv::imread load image successfully
# find_package(OpenCV REQUIRED)

# Option 2. cv::imread load empty image
# [!] Settings for the directory of OpenCV library
set(opencv_dir /Users/kcl/Documents/Cpp_Projects/library/opencv/build460/stereo-triangulate)
# set(opencv_dir /Users/kcl/Documents/Cpp_Projects/library/opencv/opencv-4.6.0/triangulate/install)
# set(opencv_dir /home/ubt/Documents/library/opencv/opencv-4.3.0/ubuntu/install)  # dell xps13 new

# Bug fixed: cv::imread load empty image
#   - when compiling opencv from scratch, mind to build with 'jpeg' & 'png' and
#   - other formats that we want to use in our project. Mind that not only
#   - DBUILD_JPEG should be ON, but also DWITH_JPEG should also be ON.

include_directories(${opencv_dir}/include/opencv4)
link_directories(${opencv_dir}/lib)

list(APPEND EXTRA_LIBS "-lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui")


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
                      ${EXTRA_LIBS}
                      imgReader
                      opencv_calib3d
                      opencv_core
                      # opencv_features2d
                      # opencv_flann
                      opencv_gapi
                      opencv_highgui
                      # opencv_img_hash
                      opencv_imgcodecs
                      # opencv_optflow
                      opencv_photo
                      opencv_video
                      opencv_videoio
                      # opencv_videostab
                      # opencv_xfeatures2d
                      # opencv_ximgproc
                      )
