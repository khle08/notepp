# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kcl/Documents/notepp/exp/11-mqtt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kcl/Documents/notepp/exp/11-mqtt/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/mqtt.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/CMakeFiles/mqtt.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/mqtt.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/mqtt.dir/flags.make

lib/CMakeFiles/mqtt.dir/mqtt.cpp.o: lib/CMakeFiles/mqtt.dir/flags.make
lib/CMakeFiles/mqtt.dir/mqtt.cpp.o: /home/kcl/Documents/notepp/exp/11-mqtt/lib/mqtt.cpp
lib/CMakeFiles/mqtt.dir/mqtt.cpp.o: lib/CMakeFiles/mqtt.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kcl/Documents/notepp/exp/11-mqtt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/mqtt.dir/mqtt.cpp.o"
	cd /home/kcl/Documents/notepp/exp/11-mqtt/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/mqtt.dir/mqtt.cpp.o -MF CMakeFiles/mqtt.dir/mqtt.cpp.o.d -o CMakeFiles/mqtt.dir/mqtt.cpp.o -c /home/kcl/Documents/notepp/exp/11-mqtt/lib/mqtt.cpp

lib/CMakeFiles/mqtt.dir/mqtt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mqtt.dir/mqtt.cpp.i"
	cd /home/kcl/Documents/notepp/exp/11-mqtt/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kcl/Documents/notepp/exp/11-mqtt/lib/mqtt.cpp > CMakeFiles/mqtt.dir/mqtt.cpp.i

lib/CMakeFiles/mqtt.dir/mqtt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mqtt.dir/mqtt.cpp.s"
	cd /home/kcl/Documents/notepp/exp/11-mqtt/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kcl/Documents/notepp/exp/11-mqtt/lib/mqtt.cpp -o CMakeFiles/mqtt.dir/mqtt.cpp.s

# Object files for target mqtt
mqtt_OBJECTS = \
"CMakeFiles/mqtt.dir/mqtt.cpp.o"

# External object files for target mqtt
mqtt_EXTERNAL_OBJECTS =

lib/libmqtt.so.1.0: lib/CMakeFiles/mqtt.dir/mqtt.cpp.o
lib/libmqtt.so.1.0: lib/CMakeFiles/mqtt.dir/build.make
lib/libmqtt.so.1.0: /home/kcl/Documents/libs/paho.mqtt.c/ubuntu/lib/libpaho-mqtt3a.so
lib/libmqtt.so.1.0: /home/kcl/Documents/libs/paho.mqtt.c/ubuntu/lib/libpaho-mqtt3c.so
lib/libmqtt.so.1.0: lib/CMakeFiles/mqtt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kcl/Documents/notepp/exp/11-mqtt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libmqtt.so"
	cd /home/kcl/Documents/notepp/exp/11-mqtt/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mqtt.dir/link.txt --verbose=$(VERBOSE)
	cd /home/kcl/Documents/notepp/exp/11-mqtt/build/lib && $(CMAKE_COMMAND) -E cmake_symlink_library libmqtt.so.1.0 libmqtt.so.1 libmqtt.so

lib/libmqtt.so.1: lib/libmqtt.so.1.0
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libmqtt.so.1

lib/libmqtt.so: lib/libmqtt.so.1.0
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libmqtt.so

# Rule to build all files generated by this target.
lib/CMakeFiles/mqtt.dir/build: lib/libmqtt.so
.PHONY : lib/CMakeFiles/mqtt.dir/build

lib/CMakeFiles/mqtt.dir/clean:
	cd /home/kcl/Documents/notepp/exp/11-mqtt/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/mqtt.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/mqtt.dir/clean

lib/CMakeFiles/mqtt.dir/depend:
	cd /home/kcl/Documents/notepp/exp/11-mqtt/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kcl/Documents/notepp/exp/11-mqtt /home/kcl/Documents/notepp/exp/11-mqtt/lib /home/kcl/Documents/notepp/exp/11-mqtt/build /home/kcl/Documents/notepp/exp/11-mqtt/build/lib /home/kcl/Documents/notepp/exp/11-mqtt/build/lib/CMakeFiles/mqtt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/mqtt.dir/depend

