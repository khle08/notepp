
mkdir build
cd build


if [[ $1 == "rm" ]]; then
	rm -rf *    # delete all contents in this "build" folder
fi

# [!] Cross compilation for HikVision device
cmake -DCMAKE_TOOLCHAIN_FILE=../sophon.cmake ..

# cmake ..
make -j4

./exe
