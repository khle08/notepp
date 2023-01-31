
function build_macos
{
	./configure \
	--prefix=$PREFIX \
	--enable-thread \
	# --host=HOST       cross-compile to build programs to run on HOST [BUILD]

	make -j4
	sudo make install
}

# PREFIX=/usr/local
PREFIX=$(pwd)/mac
build_macos
