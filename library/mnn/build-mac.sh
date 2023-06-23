
# More tags to control the compilation process please reference the following link:
#   - https://mnn-docs.readthedocs.io/en/latest/compile/cmake.html


echo "building MNN for macOS ..."

function build_macos
{
	cmake .. \
	-DCMAKE_INSTALL_PREFIX=${PREFIX} \
	-DCMAKE_BUILD_TYPE=Release \
	-DMNN_BUILD_CONVERTER=ON \
	-DMNN_BUILD_SHARED_LIBS=ON \
	-DMNN_BUILD_BENCHMARK=OFF \
	-DMNN_BUILD_QUANTOOLS=ON \
	-DMNN_WIN_RUNTIME_MT=OFF \
	-DMNN_EVALUATION=OFF \
	-DMNN_BUILD_OPENCV=OFF \
	-DMNN_BUILD_IMGCODECS=OFF \
	-DMNN_ONEDNN=OFF \
	-DMNN_AVX512=OFF \
	-DMNN_OPENCL=OFF \
        -DMNN_OPENGL=OFF \
	-DMNN_VULKAN=OFF \
	-DMNN_CUDA=OFF \
	-DMNN_TENSORRT=OFF \

	make -j4
	sudo make install
}

# PREFIX=/usr/local
PREFIX=$(pwd)/mac
mkdir build
cd build
rm -rf *

build_macos

echo "MNN compiled successfully !"
