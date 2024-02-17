
# More tags to control the compilation process please reference the following link:
#   - https://mnn-docs.readthedocs.io/en/latest/compile/cmake.html


echo "building MNN for Ubuntu ..."

function build_ubuntu
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
    -DMNN_ONEDNN=OFF \
    -DMNN_AVX512=OFF \
    -DMNN_OPENCL=OFF \
    -DMNN_OPENGL=OFF \
    -DMNN_VULKAN=OFF \
    -DMNN_CUDA=OFF   \
    -DMNN_TENSORRT=OFF \

    make -j8
    make install
}

# PREFIX=/usr/local
PREFIX=$(pwd)/ubuntu
mkdir build
cd build
rm -rf *

build_ubuntu

echo "MNN compiled successfully !"


# [CONVERTION]
# To convert onnx file into .mnn file, use the following CMD:
#   $ ./MNNConvert -f ONNX --modelFile xxx/xxx/xxx.onnx --MNNModel xxx.mnn --bizCode MNN

# [QUANTIZATION]
# To quantize model into int8 mode, use the following CMD:
#   $ ./quantized.out xxx.mnn xxx-int8.mnn pretreatConfig.json

# where the pretreatConfig.json file should include the following content:
#   {
#       "format":"RGB",
#       "mean":[
#           127.5,
#           127.5,
#           127.5
#       ],
#       "normal":[
#           0.00784314,
#           0.00784314,
#           0.00784314
#       ],
#       "width":224,
#       "height":224,
#       "path":"path/to/images/",
#       "used_image_num":500,
#       "feature_quantize_method":"KL",
#       "weight_quantize_method":"MAX_ABS"
#   }