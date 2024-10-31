
add_library(HttpServer SHARED HttpServer.cpp Controller.cpp Model.cpp View.cpp)
target_link_libraries(HttpServer PRIVATE
                      ${CMAKE_THREAD_LIBS_INIT}
                      Boost::system
                      Boost::filesystem
                      )

set_target_properties(HttpServer PROPERTIES VERSION 1.0 SOVERSION 1)
# If versions are setup, 3 libs will be generated:
# libcalibration.1.0.so / libcalibration.1.so / libcalibration.so

install(TARGETS HttpServer
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(FILES HttpServer.h Controller.h Model.h View.h DESTINATION include)

