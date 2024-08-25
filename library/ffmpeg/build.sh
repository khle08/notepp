#!/bin/bash

make uninstall
make clean
make distclean

./configure --prefix=./product \
  --enable-nonfree \
  --enable-opencl \
  --enable-asm \
  --enable-x86asm \
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
