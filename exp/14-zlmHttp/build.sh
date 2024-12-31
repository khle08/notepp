
# To install boost from source code, here are the steps:
#   1. wget https://boostorg.jfrog.io/artifactory/main/release/1.82.0/source/boost_1_82_0.tar.gz
#   2. tar -xzf boost_1_82_0.tar.gz
#   3. cd boost_1_82_0
#   4. ./boostrap.sh
#   5. sudo ./b2 install
# And Boost library will be installed to `/usr/local/include/boost` and `/usr/local/lib`


mkdir build
cd build


if [[ $1 == "rm" ]]; then
	rm -rf *    # delete all contents in this "build" folder
fi


cmake ..
make -j4

./exe

