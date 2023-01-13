
# note: This script is closer to the version that used to install on ubuntu.
#       If you want to compile more functions in ffmpeg library, use "build-macos2.sh",
#       which includes more tas without "--enable-small".

# if no --enable-shared, the following error will occurr:
# ERROR: relocation R_X86_64_PC32 against symbol ff_pw_9 can not be used when making a shared object
# ./configure --enable-shared

# if encountering following error:
# ld: symbol(s) not found for architecture x86_64
# clang: error: linker command failed with exit code 1 (use -v to see invocation)
# add "--cc=clang" to configure


function build_macos
{
	./configure \
	--prefix=$PREFIX \
	--cc=clang \
	--enable-gpl \
	--enable-libx264 \
	--enable-libx265 \
	--enable-libass \
	--enable-libfdk-aac \
	--enable-libmp3lame \
	--enable-libopus \
	--enable-opencl \
	--enable-libfreetype \
	--enable-libxvid \
	--enable-libvpx \
	--enable-small \
	--enable-nonfree \
	--enable-shared \
	--enable-static \
	--enable-ffmpeg \
	--enable-sdl2 \
	--enable-x86asm \
	--enable-libsoxr \
	--enable-libspeex \
	--enable-libbluray \
	--enable-lzma \
	--enable-gnutls \
	--enable-libfribidi \
	--enable-audiotoolbox \
	--enable-videotoolbox \
	--enable-libvorbis \
	--enable-librsvg \
	--enable-libtheora \

	make clean
	make -j4
	sudo make install
}

# PREFIX=/usr/local
PREFIX=$(pwd)/mac
build_macos
