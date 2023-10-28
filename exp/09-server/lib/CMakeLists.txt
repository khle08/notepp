
if (CMAKE_USE_OPENSSL)  # [option]
    find_package(OpenSSL REQUIRED)
    set(USE_OPENSSL "-DUSE_OPENSSL -DLIBUS_USE_OPENSSL")
    # set(OPENSSL_LIB "OpenSSL::SSL OpenSSL::Crypto")
    list(APPEND CMAKE_REQUIRED_INCLUDES ${OPENSSL_INCLUDE_DIR})
else()
    set(NOT_USE_OPENSSL "-DLIBUS_NO_SSL")
endif()


if(NOT LIBUV_INCLUDE_DIR)
    find_path(LIBUV_INCLUDE_DIR uv.h)
endif()
if(NOT LIBUV_LIBRARY)
    find_library(LIBUV_LIBRARY NAMES uv uv1)
endif()


file(GLOB SOURCES uSockets/src/*.c uSockets/src/eventing/*.c)

set(USOCKETS_EXT_INCLUDE_DIR )
set(USOCKETS_EXT_LIBS )

if (CMAKE_USE_OPENSSL)  # [option]
    # It requires C++17 or later, see https://github.com/uNetworking/uSockets/blob/0ebdde0601cc82349fc11a7c4bbb6dc5c9f28f42/Makefile#L55
    find_package(OpenSSL REQUIRED)
    file(GLOB SSL_SOURCES uSockets/src/crypto/*.c*)
    list(APPEND SOURCES ${SSL_SOURCES})
    list(APPEND USOCKETS_EXT_LIBS OpenSSL::SSL OpenSSL::Crypto)
endif()

if (CMAKE_USE_EVENT)  # [option]
    file(GLOB SSL_SOURCES uSockets/src/eventing/*.c)
    list(APPEND SOURCES ${SSL_SOURCES})
    list(APPEND USOCKETS_EXT_INCLUDE_DIR uSockets/src/internal/eventing)
endif()

if (CMAKE_USE_NETWORK)  # [option]
    list(APPEND USOCKETS_EXT_INCLUDE_DIR uSockets/src/internal/networking)
    # list(APPEND USOCKETS_EXT_LIBS ws2_32)  # This is for Windows system
endif()

add_library(uSockets ${SOURCES})

if (${LIBUS_USE_LIBUV})
  target_compile_definitions(uSockets PRIVATE -DLIBUS_USE_LIBUV)
endif()

target_compile_definitions(uSockets PRIVATE ${NOT_USE_OPENSSL} ${USE_OPENSSL})
target_include_directories(uSockets PUBLIC ${OPENSSL_INCLUDE_DIR} ${USOCKETS_EXT_INCLUDE_DIR} 
                                    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/uSockets/src")
target_link_libraries(uSockets PUBLIC ${OPENSSL_LIBRARIES} ${LIBUV_LIBRARY} ${USOCKETS_EXT_LIBS})

install(TARGETS uSockets
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

if(INSTALL_HEADERS)
    file(GLOB HEADERS uSockets/src/*.h)
    install(FILES ${HEADERS} DESTINATION include)
    file(GLOB HEADERS uSockets/src/interfaces/*.h)
    install(FILES ${HEADERS} DESTINATION include/interfaces)
endif()
