
# Brief

... more



# How to run?

### Step 1
Install arm compiler by the following CMD :

```bash
sudo apt install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu
```



### Step 2

Setup the `soc-sdk` directory in `CMakeLists.txt` to include both libraries and header files.



### Step 3

Go to the directory of this project and run the following system script :

```bash
./build.sh
# ./build.sh rm    # this CMD will remove all files in build folder first and compile code next
```

and the compilation and executable file will be automatically done and generated.



### Step 4

Move the `build` folder to sophon device:

```bash
scp -r build/ linaro@192.168.110.225:/home/linaro/algo
```

and setup the `LD_LIBRARY_PATH` in `bashrc` file if this is the first run:

```bash
echo 'export LD_LIBRARY_PATH=/home/linaro/algo/build/lib:$LD_LIBRARY_PATH' >> ~/.bashrc
source ~/.bashrc
```



### Step 5

And finally, the executable file can be run on the device.

```bash
./build/exe
```



# Other References

+ [GitHub: sophon-demo 编码后推流](https://github.com/sophgo/sophon-demo/tree/release/tutorial/video_encode)
+ [Doc: 使用 libsophon 开发（交叉编译）](https://doc.sophgo.com/sdk-docs/v24.04.01/docs_latest_release/docs/libsophon/guide/html/2_develop.html#x86)
+ [Doc: 使用 sophon-mw 开发（本地编译）](https://doc.sophgo.com/sdk-docs/v24.04.01/docs_latest_release/docs/sophon-mw/manual/html/3_develop.html)
+ [Doc: SOPHGO 多媒体框架介绍](https://doc.sophgo.com/sdk-docs/v24.04.01/docs_latest_release/docs/sophon-mw/guide/html/guide/Multimedia_Guide_zh.html#sophgo-opencv)
+ [Doc: 编译 ONNX 模型生成 .bmodel](https://doc.sophgo.com/sdk-docs/v24.04.01/docs_latest_release/docs/tpu-mlir/quick_start/html/03_onnx.html)

