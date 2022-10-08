
# Create a dynamic lib using SHARED.
add_library(say-hello SHARED say-hello/hello.cpp)
# Create a static lib using STATIC.
add_library(say-hello_static STATIC say-hello/hello.cpp)
# Change the output name of the lib.
set_target_properties(say-hello_static PROPERTIES OUTPUT_NAME say-hello)

# If there are diff types of libs with same name, use the following 2 lines to reserve them all.
set_target_properties(say-hello_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(say-hello PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# Set up the version of dynamic lib and "ln" will be done automatically.
set_target_properties(say-hello PROPERTIES VERSION 1.2 SOVERSION 3)

install(TARGETS say-hello say-hello_static
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(FILES say-hello/hello.hpp DESTINATION include/hello)
