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
CMAKE_SOURCE_DIR = /home/kcl/Documents/notepp/tools/json

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kcl/Documents/notepp/tools/json/build

# Include any dependencies generated for this target.
include CMakeFiles/expJson2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/expJson2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/expJson2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/expJson2.dir/flags.make

CMakeFiles/expJson2.dir/main2.cpp.o: CMakeFiles/expJson2.dir/flags.make
CMakeFiles/expJson2.dir/main2.cpp.o: /home/kcl/Documents/notepp/tools/json/main2.cpp
CMakeFiles/expJson2.dir/main2.cpp.o: CMakeFiles/expJson2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kcl/Documents/notepp/tools/json/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/expJson2.dir/main2.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/expJson2.dir/main2.cpp.o -MF CMakeFiles/expJson2.dir/main2.cpp.o.d -o CMakeFiles/expJson2.dir/main2.cpp.o -c /home/kcl/Documents/notepp/tools/json/main2.cpp

CMakeFiles/expJson2.dir/main2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/expJson2.dir/main2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kcl/Documents/notepp/tools/json/main2.cpp > CMakeFiles/expJson2.dir/main2.cpp.i

CMakeFiles/expJson2.dir/main2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/expJson2.dir/main2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kcl/Documents/notepp/tools/json/main2.cpp -o CMakeFiles/expJson2.dir/main2.cpp.s

CMakeFiles/expJson2.dir/dist/jsoncpp.cpp.o: CMakeFiles/expJson2.dir/flags.make
CMakeFiles/expJson2.dir/dist/jsoncpp.cpp.o: /home/kcl/Documents/notepp/tools/json/dist/jsoncpp.cpp
CMakeFiles/expJson2.dir/dist/jsoncpp.cpp.o: CMakeFiles/expJson2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kcl/Documents/notepp/tools/json/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/expJson2.dir/dist/jsoncpp.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/expJson2.dir/dist/jsoncpp.cpp.o -MF CMakeFiles/expJson2.dir/dist/jsoncpp.cpp.o.d -o CMakeFiles/expJson2.dir/dist/jsoncpp.cpp.o -c /home/kcl/Documents/notepp/tools/json/dist/jsoncpp.cpp

CMakeFiles/expJson2.dir/dist/jsoncpp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/expJson2.dir/dist/jsoncpp.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kcl/Documents/notepp/tools/json/dist/jsoncpp.cpp > CMakeFiles/expJson2.dir/dist/jsoncpp.cpp.i

CMakeFiles/expJson2.dir/dist/jsoncpp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/expJson2.dir/dist/jsoncpp.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kcl/Documents/notepp/tools/json/dist/jsoncpp.cpp -o CMakeFiles/expJson2.dir/dist/jsoncpp.cpp.s

# Object files for target expJson2
expJson2_OBJECTS = \
"CMakeFiles/expJson2.dir/main2.cpp.o" \
"CMakeFiles/expJson2.dir/dist/jsoncpp.cpp.o"

# External object files for target expJson2
expJson2_EXTERNAL_OBJECTS =

expJson2: CMakeFiles/expJson2.dir/main2.cpp.o
expJson2: CMakeFiles/expJson2.dir/dist/jsoncpp.cpp.o
expJson2: CMakeFiles/expJson2.dir/build.make
expJson2: CMakeFiles/expJson2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kcl/Documents/notepp/tools/json/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable expJson2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/expJson2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/expJson2.dir/build: expJson2
.PHONY : CMakeFiles/expJson2.dir/build

CMakeFiles/expJson2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/expJson2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/expJson2.dir/clean

CMakeFiles/expJson2.dir/depend:
	cd /home/kcl/Documents/notepp/tools/json/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kcl/Documents/notepp/tools/json /home/kcl/Documents/notepp/tools/json /home/kcl/Documents/notepp/tools/json/build /home/kcl/Documents/notepp/tools/json/build /home/kcl/Documents/notepp/tools/json/build/CMakeFiles/expJson2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/expJson2.dir/depend

