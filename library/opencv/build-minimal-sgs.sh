#!/bin/bash

# ref: https://docs.opencv.org/4.x/db/d05/tutorial_config_reference.html
#      In order to include videostab, flann / features2d / calib3d, and ...
#      ... the contrib EXTRA MODULES should be included

echo "build opencv for Ubuntu"

function build_opencv_modules
{
    cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE=../sgs.cmake \
    -DCMAKE_INSTALL_PREFIX=${PREFIX} \
    -DCMAKE_CXX_FLAGS=-std=c++11 \
    -DENABLE_CXX11=ON \
    -DBUILD_JAVA=OFF  \
    -DBUILD_CUDA_STUBS=OFF \
    -DBUILD_DOCS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_JASPER=OFF \
    -DBUILD_JPEG=ON \
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
    -DBUILD_opencv_calib3d=OFF \
    -DBUILD_opencv_core=ON \
    -DBUILD_opencv_features2d=OFF \
    -DBUILD_opencv_flann=OFF \
    -DBUILD_opencv_highgui=OFF \
    -DBUILD_opencv_gapi=OFF \
    -DBUILD_opencv_imgcodecs=ON \
    -DBUILD_opencv_imgproc=ON \
    -DBUILD_opencv_ml=OFF \
    -DBUILD_opencv_objdetect=OFF \
    -DBUILD_opencv_photo=OFF \
    -DBUILD_opencv_python2=OFF \
    -DBUILD_opencv_python3=OFF \
    -DBUILD_opencv_shape=OFF \
    -DBUILD_opencv_stitching=OFF \
    -DBUILD_opencv_superres=OFF \
    -DBUILD_opencv_ts=OFF \
    -DBUILD_opencv_video=OFF \
    -DBUILD_opencv_videoio=OFF \
    -DBUILD_opencv_world=OFF \
    -DBUILD_opencv_dnn=OFF \
    -DWITH_CLP=OFF \
    -DWITH_IPP=OFF \
    -DWITH_FFMPEG=OFF \
    -DWITH_CUDA=OFF \
    -DWITH_CUFFT=OFF \
    -DWITH_EIGEN=OFF \
    -DWITH_JASPER=OFF \
    -DWITH_JPEG=ON \
    -DWITH_PNG=OFF \
    -DWITH_PTHREADS_PF=OFF \
    -DWITH_OPENEXR=OFF \
    -DWITH_MATLAB=OFF \
    -DWITH_TBB=OFF \
    -DWITH_TIFF=OFF \
    -DWITH_WEBP=OFF \
    # -DWITH_GTK=OFF \
    # -DWITH_GTK_2_X=OFF \
    # -DEIGEN_INCLUDE_PATH=${EIGEN} \

    make clean
    make -j2
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

EXTRA_MODULES="/home/kcl/Documents/libs/opencv_contrib-4.2.0/modules"
EIGEN="/home/kcl/Documents/libs/Eigen"
build_opencv $(pwd)/sgs

