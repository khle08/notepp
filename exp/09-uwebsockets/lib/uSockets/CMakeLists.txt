cmake_minimum_required(VERSION 3.10)
project(uSockets C CXX)


# cmakelists 设置c++17
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++17 support. Please use a different C++ compiler.")
endif()

# Setup where the compiled libraries will be installed
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)


if(NOT LIBUV_INCLUDE_DIR)
    find_path(LIBUV_INCLUDE_DIR uv.h)
endif()
if(NOT LIBUV_LIBRARY)
    find_library(LIBUV_LIBRARY NAMES uv uv1)
endif()


# ======================================================================
set(ssl_dir ${CMAKE_CURRENT_SOURCE_DIR}/boringssl/install)
set(crypto_dir ${CMAKE_CURRENT_SOURCE_DIR}/boringssl/install)
set(lsquic_dir ${CMAKE_CURRENT_SOURCE_DIR}/lsquic/install)
# ======================================================================


find_package(Threads REQUIRED)

include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/src)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)


add_library(openssl STATIC IMPORTED)
set_target_properties(openssl PROPERTIES VERSION 1.0 SOVERSION 1
                      IMPORTED_LOCATION ${ssl_dir}/lib/libssl.a
                      INTERFACE_INCLUDE_DIRECTORIES ${ssl_dir})


add_library(crypto STATIC IMPORTED)
set_target_properties(crypto PROPERTIES VERSION 1.0 SOVERSION 1
                      IMPORTED_LOCATION ${crypto_dir}/lib/libcrypto.a
                      INTERFACE_INCLUDE_DIRECTORIES ${crypto_dir})


add_library(lsquic STATIC IMPORTED)
set_target_properties(lsquic PROPERTIES VERSION 1.0 SOVERSION 1
                      IMPORTED_LOCATION ${lsquic_dir}/lib/liblsquic.a
                      INTERFACE_INCLUDE_DIRECTORIES ${lsquic_dir})


file(GLOB USOCKETS_SRC src/*.c* src/eventing/*.c* src/crypto/*.c*)
add_library(uSockets ${USOCKETS_SRC})
target_compile_definitions(uSockets PRIVATE -DUSE_OPENSSL -DLIBUS_USE_OPENSSL -DLIBUS_USE_LIBUV)
target_include_directories(uSockets PUBLIC ${ssl_dir}/include ${crypto_dir}/include ${lsquic_dir}/include 
                                    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)
target_link_libraries(uSockets PUBLIC
                      ${LIBUV_LIBRARY}
                      openssl
                      crypto
                      lsquic
                      -lpthread
                      )


# install(TARGETS uSockets
#     RUNTIME DESTINATION bin
#     ARCHIVE DESTINATION lib
#     LIBRARY DESTINATION lib
# )

# if(INSTALL_HEADERS)
#     file(GLOB HEADERS src/*.h)
#     install(FILES ${HEADERS} DESTINATION include)
#     file(GLOB HEADERS src/interfaces/*.h)
#     install(FILES ${HEADERS} DESTINATION include/interfaces)
# endif()


list(APPEND SOURCE
    examples/http_server.c
)

add_executable(exe ${SOURCE})

target_link_libraries(exe PRIVATE 
                      ${CMAKE_THREAD_LIBS_INIT}
                      uSockets
                      )
