
# To install boost from source code, here are the steps:
#   1. ...
#   2. ...


mkdir build
cd build


if [[ $1 == "rm" ]]; then
	rm -rf *    # delete all contents in this "build" folder
fi


cmake ..
make -j4

./exe

