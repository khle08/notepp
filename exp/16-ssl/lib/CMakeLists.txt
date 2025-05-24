
add_library(encrypt SHARED encrypt.cpp)
target_link_libraries(encrypt PRIVATE
                      ${CMAKE_THREAD_LIBS_INIT}
                      -lcrypto
                      -lssl
                      )

set_target_properties(encrypt PROPERTIES VERSION 1.0 SOVERSION 1)
# If versions are setup, 3 libs will be generated:
# libencrypt.1.0.so / libencrypt.1.so / libencrypt.so

install(TARGETS encrypt
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(FILES encrypt.h DESTINATION include)

