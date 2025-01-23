#!/bin/bash

# Function for "upload"
upload() {
    echo "Uploading files to the environment..."
    sshpass -p "hiface123" rsync -avzP --delete -e "ssh -p 8021" ./ root@192.168.110.25:/workspace/yolo/c++/test
}

# Function for "make"
make_build() {
    echo "Preparing to make the build..."
    mkdir -p build
    cd build

    if [[ $1 == "rm" ]]; then
        echo "Removing all contents in the 'build' folder..."
        rm -rf *  # delete all contents in the "build" folder
    fi

    echo "Cross-compiling for HiS chip..."
    cmake -DCMAKE_TOOLCHAIN_FILE=../toolchains/Hi3519DV500.cmake ..
    make -j4
}

# Function for "host"
sync_host() {
    echo "Syncing files to the host environment..."
    sshpass -p "ejirmpxup" rsync -avzP --delete ./ kcl@192.168.110.50:/home/kcl/Documents/hiface/workspace/test
}

# Function for "run"
run() {
    echo "Running the program..."
    export LD_LIBRARY_PATH=/tmp/test/build/lib:$LD_LIBRARY_PATH
    ./build/exe
}

# Main logic to call functions
if [[ $1 == "u" ]]; then
    upload

elif [[ $1 == "m" ]]; then
    make_build "$2"

elif [[ $1 == "s" ]]; then
    sync_host

elif [[ $1 == "ms" ]]; then
    make_build "$2"
    cd ..
    sync_host

elif [[ $1 == "r" ]]; then
    run

else
    echo "Invalid option. Use one of the following:"
    echo "  u  - Upload files"
    echo "  m  - Make build"
    echo "  s  - Sync to host"
    echo "  r  - Run the program"
fi
