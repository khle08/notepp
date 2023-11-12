
mkdir build
cd build


if [[ $1 == "rm" ]]; then
	rm -rf *    # delete all contents in this "build" folder
fi


# These options only support ms version of CMakeLists.txt
cmake \
-DCMAKE_USE_OPENSSL=ON \
-DCMAKE_USE_EVENT=ON \
-DCMAKE_USE_NETWORK=ON \
-DCMAKE_C_COMPILER=/usr/local/bin/gcc-12 \
-DCMAKE_CXX_COMPILER=/usr/local/bin/g++-12 \
..

# The compiler can be either defined inside or outside of CMakeLists.txt

make -j4

./exe
