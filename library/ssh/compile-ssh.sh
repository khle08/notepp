# # [zlib]
# tar -zxvf zlib-1.2.11.tar.gz
# cd zlib-1.2.11

# CC=aarch64-v01c01-linux-gnu-gcc ./configure --prefix=/workspace/ssh/zlib

# make -j4
# make install
# cd ..


# # [OpenSSL]
# tar xf openssl-1.1.1g.tar.gz
cd openssl-1.1.1g

# ./config no-asm shared \
#     --cross-compile-prefix=aarch64-v01c01-linux-gnu- \
#     --prefix=/workspace/ssh/openssl
# replace 126, 127 "-m64" to "-mabi=lp64" manually

make
make install
cd ..


# [OpenSSH]
tar xf openssh-8.0p1.tar.gz
cd openssh-8.0p1

./configure --host=aarch64-linux \
    --with-libs --with-zlib=/workspace/ssh/zlib \
    --with-ssl-dir=/workspace/ssh/openssl \
    CC=aarch64-v01c01-linux-gnu-gcc \
    AR=aarch64-v01c01-linux-gnu-ar \
    --prefix=/workspace/ssh/openssh \
    --exec-prefix=/workspace/ssh/openssh \
    --disable-etc-default-login \
    --disable-strip

make -j4
make install

