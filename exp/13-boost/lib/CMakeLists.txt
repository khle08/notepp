
add_library(http SHARED http.cpp)
target_link_libraries(http PRIVATE
                      ${CMAKE_THREAD_LIBS_INIT}
                      Boost::system
                      Boost::filesystem
                      )

set_target_properties(http PROPERTIES VERSION 1.0 SOVERSION 1)
# If versions are setup, 3 libs will be generated:
# libcalibration.1.0.so / libcalibration.1.so / libcalibration.so

install(TARGETS http
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(FILES http.h DESTINATION include)

