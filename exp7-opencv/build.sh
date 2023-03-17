
mkdir build
cd build

# rm -rf *    # delete all contents in this "build" folder

cmake ..
make -j4

./expOpencv
