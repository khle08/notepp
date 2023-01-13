
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
	--enable-swscale \
	--enable-avfilter \
	--enable-libopenjpeg \
	--enable-libmodplug \
	--enable-fontconfig \
	--enable-pthreads \
	--enable-postproc \
	# --enable-avresample \
	# --enable-small \

	make clean
	make -j4
	sudo make install
}

# PREFIX=/usr/local
PREFIX=$(pwd)/mac2
build_macos
