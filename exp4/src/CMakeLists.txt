# set up the output directory for the executable file.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# declare the path for finding header files needed in our project.
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/lib)

# declare the path for finding 3rdparty libs. 
link_directories(${PROJECT_BINARY_DIR}/lib)

# compile the main cpp file to executable binary file.
add_executable(exeName main.cpp)

# pick one name to link: say-hello / say-hello_static.
target_link_libraries(exeName PRIVATE say-hello)
