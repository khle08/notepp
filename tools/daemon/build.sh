# sudo rm /tmp/daemon.log
mkdir build
cd build

if [[ $1 == "rm" ]]; then
	rm -rf *    # delete all contents in this "build" folder
fi

cmake ..
make -j4

cd ..
./build/exeName
