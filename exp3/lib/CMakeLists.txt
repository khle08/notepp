add_library(lib-name 
	    src/say-hello/hello.hpp 
	    src/say-hello/hello.cpp)

target_include_directories(lib-name PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

