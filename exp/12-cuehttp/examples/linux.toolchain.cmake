cmake_minimum_required(VERSION 3.0)

set(CMAKE_SYSTEM_NAME Linux)
SET (CMAKE_C_COMPILER "/usr/local/clang/bin/clang")
SET (CMAKE_C_FLAGS "-Wall -std=c99")
SET (CMAKE_C_FLAGS_DEBUG "-g")
SET (CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE "-O4 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")
SET (CMAKE_CXX_COMPILER "/usr/local/clang/bin/clang++")
SET (CMAKE_CXX_FLAGS "-Wall")
SET (CMAKE_CXX_FLAGS_DEBUG "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
SET (CMAKE_AR "/usr/local/clang/bin/llvm-ar")
SET (CMAKE_LINKER "/usr/local/clang/bin/llvm-ld")
SET (CMAKE_NM "/usr/local/clang/bin/llvm-nm")
SET (CMAKE_OBJDUMP "/usr/local/clang/bin/llvm-objdump")
SET (CMAKE_RANLIB "/usr/local/clang/bin/llvm-ranlib")
