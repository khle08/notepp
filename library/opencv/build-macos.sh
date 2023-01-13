#!/bin/bash

# In order to 

echo "build opencv for macOS"

function build_opencv_modules
{
    cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=${PREFIX} \
    -DCMAKE_CXX_FLAGS=-std=c++11 \
    -DENABLE_CXX11=ON \
    -DBUILD_JAVA=OFF  \
    -DBUILD_CUDA_STUBS=OFF \
    -DBUILD_DOCS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_JASPER=OFF \
    -DBUILD_JPEG=OFF \
    -DBUILD_OPENEXR=OFF \
    -DBUILD_PACKAGE=OFF \
    -DBUILD_PERF_TESTS=OFF \
    -DBUILD_PNG=OFF \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_TBB=OFF  \
    -DBUILD_TESTS=OFF \
    -DBUILD_TIFF=OFF  \
    -DBUILD_WITH_DEBUG_INFO=OFF  \
    -DBUILD_WITH_DYNAMIC_IPP=OFF  \
    -DBUILD_ZLIB=OFF  \
    -DBUILD_opencv_apps=OFF \
    -DBUILD_opencv_calib3d=ON \
    -DBUILD_opencv_core=ON \
    -DBUILD_opencv_features2d=ON \
    -DBUILD_opencv_flann=ON \
    -DBUILD_opencv_highgui=ON \
    -DBUILD_opencv_imgcodecs=ON \
    -DBUILD_opencv_imgproc=ON \
    -DBUILD_opencv_ml=OFF \
    -DBUILD_opencv_objdetect=OFF \
    -DBUILD_opencv_photo=ON \
    -DBUILD_opencv_python2=OFF \
    -DBUILD_opencv_python3=OFF \
    -DBUILD_opencv_shape=OFF \
    -DBUILD_opencv_stitching=OFF \
    -DBUILD_opencv_superres=OFF \
    -DBUILD_opencv_ts=OFF \
    -DBUILD_opencv_video=ON \
    -DBUILD_opencv_videoio=ON \
    -DBUILD_opencv_world=OFF \
    -DBUILD_opencv_dnn=OFF \
    -DWITH_CLP=ON \
    -DWITH_IPP=OFF \
    -DWITH_FFMPEG=OFF \
    -DWITH_CUDA=OFF \
    -DWITH_CUFFT=OFF \
    -DWITH_EIGEN=OFF \
    -DWITH_JASPER=OFF \
    -DWITH_JPEG=OFF \
    -DWITH_PNG=OFF \
    -DWITH_PTHREADS_PF=OFF \
    -DWITH_OPENEXR=OFF \
    -DWITH_MATLAB=OFF \
    -DWITH_TBB=OFF \
    -DWITH_TIFF=OFF \
    -DWITH_WEBP=OFF \
    -DOPENCV_EXTRA_MODULES_PATH=${EXTRA_MODULES} \
    -DBUILD_opencv_videostab=ON \
    -DBUILD_opencv_aruco=OFF \
    -DBUILD_opencv_bgsegm=OFF \
    -DBUILD_opencv_hfs=OFF \
    -DBUILD_opencv_rapid=OFF \
    -DBUILD_opencv_phase_unwrapping=OFF \
    -DBUILD_opencv_intensity_transform=OFF \
    -DBUILD_opencv_bioinspired=OFF \
    -DBUILD_opencv_ccalib=OFF \
    -DBUILD_opencv_line_descriptor=OFF \
    -DBUILD_opencv_plot=OFF \
    -DBUILD_opencv_reg=OFF \
    -DBUILD_opencv_rgbd=OFF \
    -DBUILD_opencv_xfeatures2d=ON \
    -DBUILD_opencv_saliency=OFF \
    -DBUILD_opencv_structured_light=OFF \
    -DBUILD_opencv_surface_matching=OFF \
    -DBUILD_opencv_optflow=ON \
    -DBUILD_opencv_ximgproc=ON \
    -DBUILD_opencv_xphoto=OFF \
    # -DEIGEN_INCLUDE_PATH=${EIGEN} \

    make clean
    make -j6
    make install
}

function mv_dirs {
    rm -rf $2
    mkdir -p $2
    mv $1/* $2/
}

function build_opencv {
    rm -rf $1
    mkdir $1
    cd $1

    TARGET="$1/install"
    mkdir $TARGET
    PREFIX=$TARGET

    build_opencv_modules
}

EXTRA_MODULES="/Users/kcl/Documents/Cpp_Projects/library/opencv/opencv_contrib-4.6.0/modules"
EIGEN="/Users/kcl/Documents/Cpp_Projects/library/Eigen"
build_opencv $(pwd)/mac

