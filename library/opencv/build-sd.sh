#!/bin/bash

# ref: https://docs.opencv.org/4.x/db/d05/tutorial_config_reference.html
echo "Build OpenCV 4.6.0 with all modules enabled on Ubuntu 20.04"

function build_opencv_modules
{
    cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=${PREFIX} \
    -DCMAKE_CXX_FLAGS=-std=c++11 \
    -DENABLE_CXX11=ON \
    -DOPENCV_DISABLE_FILESYSTEM_SUPPORT=OFF \
    -DCUDA_TOOLKIT_ROOT_DIR=/usr/local/cuda-11.8 \
    -DBUILD_JAVA=OFF \
    -DBUILD_opencv_python2=OFF \
    -DBUILD_opencv_python3=ON \
    -DBUILD_CUDA_STUBS=OFF \
    -DWITH_CUDA=ON \
    -DWITH_CUFFT=ON \
    -DWITH_TBB=ON \
    -DWITH_IPP=OFF \
    -DWITH_OPENMP=ON \
    -DBUILD_DOCS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_PERF_TESTS=OFF \
    -DBUILD_TESTS=OFF \
    -DBUILD_JASPER=OFF \
    -DBUILD_JPEG=ON \
    -DBUILD_OPENEXR=ON \
    -DBUILD_PNG=ON \
    -DBUILD_TIFF=ON \
    -DBUILD_WEBP=ON \
    -DBUILD_ZLIB=ON \
    -DWITH_JASPER=OFF \
    -DWITH_JPEG=ON \
    -DWITH_PNG=ON \
    -DWITH_TIFF=ON \
    -DWITH_WEBP=ON \
    -DWITH_OPENEXR=ON \
    -DBUILD_PACKAGE=OFF \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_WITH_DEBUG_INFO=OFF \
    -DBUILD_WITH_DYNAMIC_IPP=OFF \
    -DBUILD_opencv_apps=ON \
    -DBUILD_opencv_calib3d=ON \
    -DBUILD_opencv_core=ON \
    -DBUILD_opencv_dnn=ON \
    -DBUILD_opencv_features2d=ON \
    -DBUILD_opencv_flann=ON \
    -DBUILD_opencv_highgui=ON \
    -DBUILD_opencv_imgcodecs=ON \
    -DBUILD_opencv_imgproc=ON \
    -DBUILD_opencv_ml=ON \
    -DBUILD_opencv_objdetect=ON \
    -DBUILD_opencv_photo=ON \
    -DBUILD_opencv_shape=ON \
    -DBUILD_opencv_stitching=ON \
    -DBUILD_opencv_superres=ON \
    -DBUILD_opencv_ts=ON \
    -DBUILD_opencv_video=ON \
    -DBUILD_opencv_videoio=ON \
    -DBUILD_opencv_videostab=ON \
    -DBUILD_opencv_world=OFF \
    -DWITH_CLP=ON \
    -DWITH_FFMPEG=ON \
    -DWITH_EIGEN=ON \
    -DWITH_GTK=ON \
    -DWITH_MATLAB=OFF \
    -DWITH_OPENGL=ON \
    -DWITH_QT=OFF \
    -DWITH_V4L=ON \
    -DWITH_PTHREADS_PF=ON \
    -DOPENCV_EXTRA_MODULES_PATH=${EXTRA_MODULES} \
    -DBUILD_opencv_tracking=ON \
    -DBUILD_opencv_barcode=ON \
    -DBUILD_opencv_datasets=ON \
    -DBUILD_opencv_dnn_objdetect=ON \
    -DBUILD_opencv_dnn_superres=ON \
    -DBUILD_opencv_dpm=ON \
    -DBUILD_opencv_face=ON \
    -DBUILD_opencv_mcc=ON \
    -DBUILD_opencv_quality=ON \
    -DBUILD_opencv_text=ON \
    -DBUILD_opencv_wechat_qrcode=ON \
    -DBUILD_opencv_xobjdetect=ON \
    -DBUILD_opencv_alphamat=ON \
    -DBUILD_opencv_stereo=ON \
    -DBUILD_opencv_freetype=ON \
    -DBUILD_opencv_fuzzy=ON \
    -DBUILD_opencv_aruco=ON \
    -DBUILD_opencv_bgsegm=ON \
    -DBUILD_opencv_hfs=ON \
    -DBUILD_opencv_rapid=ON \
    -DBUILD_opencv_phase_unwrapping=ON \
    -DBUILD_opencv_intensity_transform=ON \
    -DBUILD_opencv_bioinspired=ON \
    -DBUILD_opencv_ccalib=ON \
    -DBUILD_opencv_line_descriptor=ON \
    -DBUILD_opencv_plot=ON \
    -DBUILD_opencv_reg=ON \
    -DBUILD_opencv_rgbd=ON \
    -DBUILD_opencv_xfeatures2d=ON \
    -DBUILD_opencv_saliency=ON \
    -DBUILD_opencv_structured_light=ON \
    -DBUILD_opencv_surface_matching=ON \
    -DBUILD_opencv_optflow=ON \
    -DBUILD_opencv_ximgproc=ON \
    -DBUILD_opencv_xphoto=ON \
    # -DEIGEN_INCLUDE_PATH=/usr/include/eigen3

    make clean
    make -j$(nproc)
    sudo make install
    sudo ldconfig
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

# 配置路径（根据您的 Ubuntu 环境调整）
EXTRA_MODULES="/home/wentian/.lib/opencv/opencv_contrib-4.6.0/modules"
build_opencv $(pwd)/ubuntu-sd
