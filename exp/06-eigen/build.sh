
mkdir build
cd build

if [[ $1 == "rm" ]]; then
	rm -rf *
fi

cmake ..
make -j4

./exe
