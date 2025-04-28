
# Add this tag: -DNO_STD_LIB=1
./genMakefiles macosx-no-openssl
# The key "macosx-no-openssl" is the name behind "config." and the setups are defined in the file

make -j4

mkdir compile
make install PREFIX=/path/to/compile

