
# ref: https://github.com/berndporr/kiss-fft


echo "build berndporr/kiss-fft for macOS"

function build_macos
{
    cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=${PREFIX} \


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
