
# More tags to control the compilation process please reference the following link:
#   - https://mnn-docs.readthedocs.io/en/latest/compile/cmake.html

# Introduction to parameters:
#   -DCMAKE_INSTALL_PREFIX=${PREFIX}           : Define where to make install
#   -DPAHO_BUILD_SHARED=TRUE                   : Build a shared version of the libraries
#   -DPAHO_BUILD_STATIC=FALSE                  : Build a static version of the libraries
#   -DPAHO_HIGH_PERFORMANCE=FALSE              : When set to true, the debugging aids internal tracing and heap tracking are not included
#   -DPAHO_WITH_SSL=FALSE                      : Flag that defines whether to build ssl-enabled binaries too
#   -DOPENSSL_ROOT_DIR=""                      : Directory containing OpenSSL installation (i.e. /usr/local)
#   -DPAHO_BUILD_DOCUMENTATION=FALSE           : Create and install the HTML based API documentation (requires Doxygen)
#   -DPAHO_BUILD_SAMPLES=FALSE                 : Build sample programs
#   -DPAHO_ENABLE_TESTING=TRUE                 : Build test and run
#   -DMQTT_TEST_BROKER="tcp://localhost:1883"  : MQTT connection URL for a broker to use during test execution
#   -DMQTT_TEST_PROXY="tcp://localhost:1883"   : Hostname of the test proxy to use
#   -DMQTT_SSL_HOSTNAME="localhost"            : Hostname of a test SSL MQTT broker to use
#   -DPAHO_BUILD_DEB_PACKAGE=FALSE             : Build debian package


echo "building paho.mqtt library for ubuntu ..."

function build_macos
{
    cmake .. \
    -DCMAKE_INSTALL_PREFIX=${PREFIX} \
    -DPAHO_BUILD_SHARED=TRUE \
    -DPAHO_BUILD_STATIC=FALSE \
    -DPAHO_HIGH_PERFORMANCE=FALSE \
    -DPAHO_WITH_SSL=FALSE \
    -DOPENSSL_ROOT_DIR="" \
    -DPAHO_BUILD_DOCUMENTATION=FALSE \
    -DPAHO_BUILD_SAMPLES=FALSE \
    -DPAHO_ENABLE_TESTING=TRUE \
    -DMQTT_TEST_BROKER="tcp://localhost:1883" \
    -DMQTT_TEST_PROXY="tcp://localhost:1883" \
    -DMQTT_SSL_HOSTNAME="localhost" \
    -DPAHO_BUILD_DEB_PACKAGE=FALSE \

    make -j4
    sudo make install
}

# PREFIX=/usr/local
PREFIX=$(pwd)/ubuntu
mkdir build
cd build
rm -rf *

build_macos

echo "paho.mqtt compiled successfully !"
