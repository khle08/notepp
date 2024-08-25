1. Install cuda video sdk
 - Download Video_Codec_SDK_11.1: https://developer.nvidia.com/video-codec-sdk-archive
 - Copy headers into system: 
```
 sudo cp ~/Downloads/Video_Codec_SDK_11.1.5/Interface/* /usr/local/cuda/include
```
2. Install ffnvcodec
 - Clone nv-codec-headers: git clone https://git.videolan.org/git/ffmpeg/nv-codec-headers.git
 - Checkout branch sdk/11.1
 - Install: make install
 - Or uninstall: make Uninstall && make clean && make distclean
3. Build x264
 - 
```
#!/bin/bash

#git clone https://codec.videolan.org/videolan/x264
make uninstall
make clean
make distclean

./configure --enable-shared --disable-asm --prefix=/usr/local/x264

make -j16
make install
```
4. Build ffmpeg
```
#!/bin/bash

make uninstall
make clean
make distclean

./configure --prefix=./product \
  --enable-nonfree \
  --enable-gpl \
  --enable-ffnvcodec \
  --enable-cuda \
  --enable-cuvid \
  --enable-nvenc \
  --enable-libnpp \
  --enable-libx264 \
  --enable-static \
  --disable-shared \
  --extra-cflags="-I/usr/local/cuda/include -I/usr/local/x264/include" \
  --extra-ldflags="-L/usr/local/cuda/lib64 -L/usr/local/x264/lib" \

make -j16
make install
```
