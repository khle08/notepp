
mkdir build
cd build

if [[ $1 == "rm" ]]; then
	rm -rf *    # delete all contents in this "build" folder
fi

# Cross compilation for HikVision device
cmake -DCMAKE_TOOLCHAIN_FILE=../rk1126.cmake ..

# Regular compilation for a computer
# cmake ..

make -j4

# chmod +777 -R *
sshpass -p "admin888" scp -r * root@192.168.110.222:/tmp/jingwei/build

# cd ..
# ./build/exeName
