
add_library(assign SHARED assign/munkres.cpp)
set_target_properties(assign PROPERTIES VERSION 1.0 SOVERSION 1)
# If versions are setup, 3 libs will be generated:
# libcalibration.1.0.so / libcalibration.1.so / libcalibration.so

install(TARGETS assign
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(FILES assign/munkres.h DESTINATION include)

