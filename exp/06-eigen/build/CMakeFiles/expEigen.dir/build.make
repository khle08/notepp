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
CMAKE_SOURCE_DIR = /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/build

# Include any dependencies generated for this target.
include CMakeFiles/expEigen.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/expEigen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/expEigen.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/expEigen.dir/flags.make

CMakeFiles/expEigen.dir/main.cpp.o: CMakeFiles/expEigen.dir/flags.make
CMakeFiles/expEigen.dir/main.cpp.o: /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/main.cpp
CMakeFiles/expEigen.dir/main.cpp.o: CMakeFiles/expEigen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/expEigen.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/expEigen.dir/main.cpp.o -MF CMakeFiles/expEigen.dir/main.cpp.o.d -o CMakeFiles/expEigen.dir/main.cpp.o -c /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/main.cpp

CMakeFiles/expEigen.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/expEigen.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/main.cpp > CMakeFiles/expEigen.dir/main.cpp.i

CMakeFiles/expEigen.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/expEigen.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/main.cpp -o CMakeFiles/expEigen.dir/main.cpp.s

# Object files for target expEigen
expEigen_OBJECTS = \
"CMakeFiles/expEigen.dir/main.cpp.o"

# External object files for target expEigen
expEigen_EXTERNAL_OBJECTS =

expEigen: CMakeFiles/expEigen.dir/main.cpp.o
expEigen: CMakeFiles/expEigen.dir/build.make
expEigen: lib/libassign.1.0.dylib
expEigen: CMakeFiles/expEigen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable expEigen"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/expEigen.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/expEigen.dir/build: expEigen
.PHONY : CMakeFiles/expEigen.dir/build

CMakeFiles/expEigen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/expEigen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/expEigen.dir/clean

CMakeFiles/expEigen.dir/depend:
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/build /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/build /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/build/CMakeFiles/expEigen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/expEigen.dir/depend

