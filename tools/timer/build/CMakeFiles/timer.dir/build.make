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
CMAKE_SOURCE_DIR = /Users/kcl/Documents/Cpp_Projects/notepp/tools/timer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/kcl/Documents/Cpp_Projects/notepp/tools/timer/build

# Include any dependencies generated for this target.
include CMakeFiles/timer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/timer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/timer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/timer.dir/flags.make

CMakeFiles/timer.dir/timer.cpp.o: CMakeFiles/timer.dir/flags.make
CMakeFiles/timer.dir/timer.cpp.o: /Users/kcl/Documents/Cpp_Projects/notepp/tools/timer/timer.cpp
CMakeFiles/timer.dir/timer.cpp.o: CMakeFiles/timer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kcl/Documents/Cpp_Projects/notepp/tools/timer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/timer.dir/timer.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/timer.dir/timer.cpp.o -MF CMakeFiles/timer.dir/timer.cpp.o.d -o CMakeFiles/timer.dir/timer.cpp.o -c /Users/kcl/Documents/Cpp_Projects/notepp/tools/timer/timer.cpp

CMakeFiles/timer.dir/timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/timer.dir/timer.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kcl/Documents/Cpp_Projects/notepp/tools/timer/timer.cpp > CMakeFiles/timer.dir/timer.cpp.i

CMakeFiles/timer.dir/timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/timer.dir/timer.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kcl/Documents/Cpp_Projects/notepp/tools/timer/timer.cpp -o CMakeFiles/timer.dir/timer.cpp.s

# Object files for target timer
timer_OBJECTS = \
"CMakeFiles/timer.dir/timer.cpp.o"

# External object files for target timer
timer_EXTERNAL_OBJECTS =

libtimer.a: CMakeFiles/timer.dir/timer.cpp.o
libtimer.a: CMakeFiles/timer.dir/build.make
libtimer.a: CMakeFiles/timer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kcl/Documents/Cpp_Projects/notepp/tools/timer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libtimer.a"
	$(CMAKE_COMMAND) -P CMakeFiles/timer.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/timer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/timer.dir/build: libtimer.a
.PHONY : CMakeFiles/timer.dir/build

CMakeFiles/timer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/timer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/timer.dir/clean

CMakeFiles/timer.dir/depend:
	cd /Users/kcl/Documents/Cpp_Projects/notepp/tools/timer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kcl/Documents/Cpp_Projects/notepp/tools/timer /Users/kcl/Documents/Cpp_Projects/notepp/tools/timer /Users/kcl/Documents/Cpp_Projects/notepp/tools/timer/build /Users/kcl/Documents/Cpp_Projects/notepp/tools/timer/build /Users/kcl/Documents/Cpp_Projects/notepp/tools/timer/build/CMakeFiles/timer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/timer.dir/depend

