
add_library(HttpKits SHARED routers.cpp middlewares.cpp)
target_link_libraries(HttpKits PRIVATE
                      ${_INTERFACE_OR_PUBLIC}
                      Threads::Threads
                      -lpthread
                      # Needed for Windows libs on Mingw, as the pragma comment(lib, "xyz") aren't triggered.
                      $<$<PLATFORM_ID:Windows>:ws2_32>
                      $<$<PLATFORM_ID:Windows>:crypt32>
                      # Needed for API from MacOS Security framework
                      "$<$<AND:$<PLATFORM_ID:Darwin>,$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>,$<BOOL:${HTTPLIB_USE_CERTS_FROM_MACOSX_KEYCHAIN}>>:-framework CoreFoundation -framework Security>"
                      # Can't put multiple targets in a single generator expression or it bugs out.
                      $<$<BOOL:${HTTPLIB_IS_USING_BROTLI}>:Brotli::common>
                      $<$<BOOL:${HTTPLIB_IS_USING_BROTLI}>:Brotli::encoder>
                      $<$<BOOL:${HTTPLIB_IS_USING_BROTLI}>:Brotli::decoder>
                      $<$<BOOL:${HTTPLIB_IS_USING_ZLIB}>:ZLIB::ZLIB>
                      $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:OpenSSL::SSL>
                      $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:OpenSSL::Crypto>
                      )

# Set the definitions to enable optional features
target_compile_definitions(${PROJECT_NAME} ${_INTERFACE_OR_PUBLIC}
    $<$<BOOL:${HTTPLIB_NO_EXCEPTIONS}>:CPPHTTPLIB_NO_EXCEPTIONS>
    $<$<BOOL:${HTTPLIB_IS_USING_BROTLI}>:CPPHTTPLIB_BROTLI_SUPPORT>
    $<$<BOOL:${HTTPLIB_IS_USING_ZLIB}>:CPPHTTPLIB_ZLIB_SUPPORT>
    $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:CPPHTTPLIB_OPENSSL_SUPPORT>
    $<$<AND:$<PLATFORM_ID:Darwin>,$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>,$<BOOL:${HTTPLIB_IS_USING_CERTS_FROM_MACOSX_KEYCHAIN}>>:CPPHTTPLIB_USE_CERTS_FROM_MACOSX_KEYCHAIN>
)

set_target_properties(HttpKits PROPERTIES VERSION 1.0 SOVERSION 1)
# If versions are setup, 3 libs will be generated:
# libcalibration.1.0.so / libcalibration.1.so / libcalibration.so

install(TARGETS HttpKits
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(FILES routers.h middlewares.h DESTINATION include)

