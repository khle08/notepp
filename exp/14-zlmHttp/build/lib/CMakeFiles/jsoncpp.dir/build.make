# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.25.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.25.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/jsoncpp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/CMakeFiles/jsoncpp.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/jsoncpp.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/jsoncpp.dir/flags.make

lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_reader.cpp.o: lib/CMakeFiles/jsoncpp.dir/flags.make
lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_reader.cpp.o: /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/lib/jsoncpp/json_reader.cpp
lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_reader.cpp.o: lib/CMakeFiles/jsoncpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_reader.cpp.o"
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/build/lib && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_reader.cpp.o -MF CMakeFiles/jsoncpp.dir/jsoncpp/json_reader.cpp.o.d -o CMakeFiles/jsoncpp.dir/jsoncpp/json_reader.cpp.o -c /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/lib/jsoncpp/json_reader.cpp

lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp.dir/jsoncpp/json_reader.cpp.i"
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/build/lib && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/lib/jsoncpp/json_reader.cpp > CMakeFiles/jsoncpp.dir/jsoncpp/json_reader.cpp.i

lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp.dir/jsoncpp/json_reader.cpp.s"
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/build/lib && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/lib/jsoncpp/json_reader.cpp -o CMakeFiles/jsoncpp.dir/jsoncpp/json_reader.cpp.s

lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_value.cpp.o: lib/CMakeFiles/jsoncpp.dir/flags.make
lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_value.cpp.o: /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/lib/jsoncpp/json_value.cpp
lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_value.cpp.o: lib/CMakeFiles/jsoncpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_value.cpp.o"
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/build/lib && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_value.cpp.o -MF CMakeFiles/jsoncpp.dir/jsoncpp/json_value.cpp.o.d -o CMakeFiles/jsoncpp.dir/jsoncpp/json_value.cpp.o -c /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/lib/jsoncpp/json_value.cpp

lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_value.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp.dir/jsoncpp/json_value.cpp.i"
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/build/lib && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/lib/jsoncpp/json_value.cpp > CMakeFiles/jsoncpp.dir/jsoncpp/json_value.cpp.i

lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_value.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp.dir/jsoncpp/json_value.cpp.s"
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/build/lib && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/lib/jsoncpp/json_value.cpp -o CMakeFiles/jsoncpp.dir/jsoncpp/json_value.cpp.s

lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_writer.cpp.o: lib/CMakeFiles/jsoncpp.dir/flags.make
lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_writer.cpp.o: /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/lib/jsoncpp/json_writer.cpp
lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_writer.cpp.o: lib/CMakeFiles/jsoncpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_writer.cpp.o"
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/build/lib && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_writer.cpp.o -MF CMakeFiles/jsoncpp.dir/jsoncpp/json_writer.cpp.o.d -o CMakeFiles/jsoncpp.dir/jsoncpp/json_writer.cpp.o -c /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/lib/jsoncpp/json_writer.cpp

lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_writer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp.dir/jsoncpp/json_writer.cpp.i"
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/build/lib && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/lib/jsoncpp/json_writer.cpp > CMakeFiles/jsoncpp.dir/jsoncpp/json_writer.cpp.i

lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_writer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp.dir/jsoncpp/json_writer.cpp.s"
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/build/lib && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/lib/jsoncpp/json_writer.cpp -o CMakeFiles/jsoncpp.dir/jsoncpp/json_writer.cpp.s

# Object files for target jsoncpp
jsoncpp_OBJECTS = \
"CMakeFiles/jsoncpp.dir/jsoncpp/json_reader.cpp.o" \
"CMakeFiles/jsoncpp.dir/jsoncpp/json_value.cpp.o" \
"CMakeFiles/jsoncpp.dir/jsoncpp/json_writer.cpp.o"

# External object files for target jsoncpp
jsoncpp_EXTERNAL_OBJECTS =

lib/libjsoncpp.a: lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_reader.cpp.o
lib/libjsoncpp.a: lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_value.cpp.o
lib/libjsoncpp.a: lib/CMakeFiles/jsoncpp.dir/jsoncpp/json_writer.cpp.o
lib/libjsoncpp.a: lib/CMakeFiles/jsoncpp.dir/build.make
lib/libjsoncpp.a: lib/CMakeFiles/jsoncpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libjsoncpp.a"
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/jsoncpp.dir/cmake_clean_target.cmake
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jsoncpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/jsoncpp.dir/build: lib/libjsoncpp.a
.PHONY : lib/CMakeFiles/jsoncpp.dir/build

lib/CMakeFiles/jsoncpp.dir/clean:
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/jsoncpp.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/jsoncpp.dir/clean

lib/CMakeFiles/jsoncpp.dir/depend:
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/lib /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/build /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/build/lib /Users/kcl/Documents/Cpp_Projects/notepp/exp/14-zlmHttp/build/lib/CMakeFiles/jsoncpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/jsoncpp.dir/depend

