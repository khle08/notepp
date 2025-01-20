mkdir build
cd build
rm -rf *

# Cross compilation for HikVision device
# cmake -DCMAKE_TOOLCHAIN_FILE=../rk1126.cmake ..

# Regular compilation for a computer
cmake ..

make -j2
./bin/exeName
