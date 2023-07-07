
add_library(socket SHARED client.cpp server.cpp)
target_link_libraries(socket PRIVATE
                      ${CMAKE_THREAD_LIBS_INIT}
                      )

set_target_properties(socket PROPERTIES VERSION 1.0 SOVERSION 1)
# If versions are setup, 3 libs will be generated:
# libcalibration.1.0.so / libcalibration.1.so / libcalibration.so

install(TARGETS socket
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(FILES client.h server.h DESTINATION include)

