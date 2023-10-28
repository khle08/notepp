
mkdir build
cd build


if [[ $1 == "rm" ]]; then
	rm -rf *    # delete all contents in this "build" folder
fi


# These options only support ms version of CMakeLists.txt
cmake -DCMAKE_USE_OPENSSL=OFF -DCMAKE_USE_EVENT=ON -DCMAKE_USE_NETWORK=ON ..
make -j4

./exe
