set(CMAKE_SYSTEM_NAME Windows)
# set(CMAKE_SYSTEM_PROCESSOR x86)

# set(tools /home/ubt/Documents/compilation/arm-ca9-linux-gnueabihf-6.5)  # dell-3090
# set(tools /home/kcl/Documents/tools/compile/arm-ca9-linux-gnueabihf-6.5)  # dell-16

# do not use "...-gcc" for windows or "mutex" will raise en error. See the ref links:
#    - https://steward-fu.github.io/website/program/mingw/fix_posix.htm
#    - https://stackoverflow.com/questions/17242516/mingw-w64-threads-posix-vs-win32
set(CMAKE_C_COMPILER /usr/bin/x86_64-w64-mingw32-gcc-posix)
set(CMAKE_CXX_COMPILER /usr/bin/x86_64-w64-mingw32-g++-posix)

# # search for programs in the build host directories (not necessary)
# SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# # for libraries and headers in the target directories
# SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)


# !!!!! FAILED !!!!!