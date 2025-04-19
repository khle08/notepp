#!/bin/bash

# Get current directory
CURRENT_DIR="$(pwd)"

# Parse platform parameter
if [ -z "${1}" ]; then
    echo "Usage: ${0} [platform]"
    echo "  Supported platforms:"
    echo "  hi3519dv500 | hi3516dv500      - HiSilicon 19DV500 | 16DV500 platform"
    echo "  hi3516cv610                    - HiSilicon 16CV610 platform"
    echo "  ss928 | sd3403                 - HiSilicon SS928"
    echo "  ss524                          - HiSilicon SS524"
    echo "  help                           - Show this help message"
    exit 0
fi

# Set cross-compiler prefix based on platform
case "${1}" in
    "sd3403" | "ss928")
        CROSS_HOST="aarch64-mix210-linux"
        ;;
    "ss524")
        CROSS_HOST="arm-mix410-linux"
        ;;
    "hi3519dv500" | "hi3516dv500")
        CROSS_HOST="aarch64-v01c01-linux-gnu"
        ;;
    "hi3516cv610")
        CROSS_HOST="arm-v01c02-linux-musleabi"
        ;;
    "help")
        echo "Usage: ${0} [platform]"
        echo "  Supported platforms:"
        echo "  hi3519dv500 | hi3516dv500      - HiSilicon 19DV500 | 16DV500 platform"
        echo "  hi3516cv610                    - HiSilicon 16CV610 platform"
        echo "  ss928 | sd3403                 - HiSilicon SS928"
        echo "  ss524                          - HiSilicon SS524"
        echo "  help                           - Show this help message"
        exit 0
        ;;
    *)
        echo "Error: Unknown platform '${1}'"
        echo "Use '${0} help' for usage"
        exit 1
        ;;
esac

# Configure compiler and paths
CROSS_COMPILE_PREFIX="${CROSS_HOST}"
CC="${CROSS_COMPILE_PREFIX}-gcc"
INSTALL_PATH="${CURRENT_DIR}/install_${1}"
BUILD_TMP_DIR="${CURRENT_DIR}/tmp"
THREAD_NUM=2

# Create directories
mkdir -p "${INSTALL_PATH}"
mkdir -p "${BUILD_TMP_DIR}"

# Path for the generated toolchain file
TOOLCHAIN_FILE="${BUILD_TMP_DIR}/cmake/aarch64.cmake"

# Create the aarch64.cmake toolchain file
echo "Creating the aarch64.cmake toolchain file ..."
mkdir -p "$(dirname "${TOOLCHAIN_FILE}")"

cat > "${TOOLCHAIN_FILE}" <<EOL
# Toolchain file for cross-compilation to ARM

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Set the cross-compilation tools
set(CMAKE_C_COMPILER "${CROSS_COMPILE_PREFIX}-gcc")
set(CMAKE_CXX_COMPILER "${CROSS_COMPILE_PREFIX}-g++")
set(CMAKE_STRIP "${CROSS_COMPILE_PREFIX}-strip")
set(CMAKE_ASM_COMPILER "${CROSS_COMPILE_PREFIX}-gcc")
EOL

# Build OpenSSL
echo "Building OpenSSL ..."
tar -xvzf opensource/openssl-1.1.1k.tar.gz -C "${BUILD_TMP_DIR}"
cd "${BUILD_TMP_DIR}/openssl-1.1.1k" || exit
./config no-asm --prefix="${INSTALL_PATH}" --cross-compile-prefix="${CROSS_COMPILE_PREFIX}"

# Remove '-m64' from the Makefile
echo "Removing '-m64' from the Makefile ..."
sed -i 's/-m64//g' Makefile

make -j "${THREAD_NUM}"
make install
cd "${CURRENT_DIR}" || exit

# Build libsrtp with CMake
echo "Building libsrtp with CMake ..."
tar -xvzf opensource/libsrtp-2.3.0.tar.gz -C "${BUILD_TMP_DIR}"
cd "${BUILD_TMP_DIR}/libsrtp-2.3.0" || exit

mkdir -p build
cd build
cmake .. \
    -DCMAKE_TOOLCHAIN_FILE="${TOOLCHAIN_FILE}" \
    -DCMAKE_INSTALL_PREFIX="${INSTALL_PATH}" \
    -DBUILD_SHARED_LIBS=ON \
    -DENABLE_OPENSSL=ON \
    -DOPENSSL_ROOT_DIR="${INSTALL_PATH}"
make -j "${THREAD_NUM}"
make install
cd "${CURRENT_DIR}" || exit

# Extract and build ZLMediaKit
echo "Extracting ZLMediaKit ..."
cd "${BUILD_TMP_DIR}/ZLMediaKit" || exit
mkdir build
cd build

cmake .. \
    -DCMAKE_TOOLCHAIN_FILE="${TOOLCHAIN_FILE}" \
    -DENABLE_WEBRTC=ON \
    -DENABLE_OPENSSL=ON \
    -DDISABLE_REPORT=ON \
    -DENABLE_TESTS=OFF \
    -DCMAKE_BUILD_TYPE=Release \
    -DOPENSSL_ROOT_DIR="${INSTALL_PATH}" \
    -DOPENSSL_LIBRARIES="${INSTALL_PATH}/lib" \
    -DCMAKE_PREFIX_PATH="${INSTALL_PATH}" \
    -DCMAKE_INSTALL_PREFIX="${INSTALL_PATH}"

make -j "${THREAD_NUM}"
make install
cd "${CURRENT_DIR}" || exit

# Clean up
rm -rf "${BUILD_TMP_DIR}"
echo "Build process completed successfully"