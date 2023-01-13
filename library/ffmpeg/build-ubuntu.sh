# sudo apt update
# sudo apt install -y build-essential libass-dev libgpac-dev
# sudo apt install -y libsdl1.2-dev libtheora-dev libtool
# sudo apt install -y libfdk-aac-dev libx264-dev libx265-dev
# sudo apt install -y libc6 libc6-dev libm3lame-dev nasm yasm


# if no --enable-shared, the following error will occurr:
# ERROR: relocation R_X86_64_PC32 against symbol ff_pw_9 can not be used when making a shared object
# ./configure --enable-shared


function build_ubuntu
{
	# --cc=clang \
	./configure \
	--prefix=$PREFIX \
	--enable-gpl \
	--enable-libx264 \
	--enable-libx265 \
	--enable-libass \
	--enable-libfdk-aac \
	--enable-libmp3lame \
	--enable-libopus \
	--enable-libtheora \
	--enable-libvorbis \
	--enable-libvpx \
	--enable-small \
	--enable-nonfree \
	--enable-shared \
	--enable-static \
	--enable-ffmpeg \
	--enable-opencl \

	# The followings are the functions that need CUDA
	# --enable-cuda-nvcc \
	# --enable-libnpp \
	# --extra-cflags=-I/usr/local/cuda/include \
	# --extra-ldflags=-L/usr/local/cuda/lib64 \

	make clean
	make -j2
	sudo make install
}

# PREFIX=/usr/local
PREFIX=$(pwd)/ubuntu
build_ubuntu
