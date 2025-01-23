
add_library(imgReader SHARED imgReader.cpp)
target_link_libraries(imgReader PRIVATE
                      ${CMAKE_THREAD_LIBS_INIT}
                      ${FFMPEG_LIBS}
                      ${OpenCV_LIBS}
                      )

set_target_properties(imgReader PROPERTIES VERSION 1.0 SOVERSION 1)
# If versions are setup, 3 libs will be generated:
# libcalibration.1.0.so / libcalibration.1.so / libcalibration.so

install(TARGETS imgReader
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(FILES imgReader.h DESTINATION include)

