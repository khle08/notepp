
mkdir build
cd build

cmake -DCMAKE_TOOLCHAIN_FILE=../toolchains/Hi3519DV500.cmake \
      -DCMAKE_INSTALL_PREFIX=/workspace/opencv-mobile-4.10.0/install \
      -DCMAKE_BUILD_TYPE=Release \
      `cat ../options.txt` \
      -DBUILD_opencv_world=OFF ..

make -j4
make install
