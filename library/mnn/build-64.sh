#!/bin/bash

mkdir build
cd build
rm -rf *

cmake .. \
-DCMAKE_TOOLCHAIN_FILE=/Users/guojunlin/Library/Android/sdk/ndk/21.4.7075529/build/cmake/android.toolchain.cmake \
-DCMAKE_INSTALL_PREFIX="$(pwd)/android" \
-DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
-DCMAKE_BUILD_TYPE=Release \
-DANDROID_ABI="armeabi-v7a" \
-DANDROID_STL=c++_static \
-DMNN_USE_LOGCAT=false \
-DMNN_BUILD_BENCHMARK=ON \
-DMNN_USE_SSE=OFF \
-DMNN_SUPPORT_BF16=ON \
-DMNN_BUILD_TEST=ON \
-DANDROID_NATIVE_API_LEVEL=android-21  \
-DMNN_BUILD_FOR_ANDROID_COMMAND=true \
-DNATIVE_LIBRARY_OUTPUT=. -DNATIVE_INCLUDE_OUTPUT=. $1 $2 $3

make -j4
make install
