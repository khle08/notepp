
# ref: https://github.com/anthonix/ffts


echo "build anthonix/ffts for macOS"

function build_macos
{
    cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=${PREFIX} \
    -DCMAKE_CXX_FLAGS=-std=c++11 \
    -DENABLE_CXX11=ON \


    make clean
    make -j4
    make install
}

rm -rf build
mkdir -p build
cd build

# PREFIX=/usr/local
PREFIX=$(pwd)/mac
build_macos
