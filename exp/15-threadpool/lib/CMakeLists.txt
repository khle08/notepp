
add_library(threadPool SHARED threadPool.cpp)
target_link_libraries(threadPool PRIVATE
                      ${CMAKE_THREAD_LIBS_INIT}
                      )

set_target_properties(threadPool PROPERTIES VERSION 1.0 SOVERSION 1)
# If versions are setup, 3 libs will be generated:
# libcalibration.1.0.so / libcalibration.1.so / libcalibration.so

install(TARGETS threadPool
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(FILES threadPool.h DESTINATION include)

