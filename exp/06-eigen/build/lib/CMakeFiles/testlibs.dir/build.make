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
include lib/CMakeFiles/testlibs.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/CMakeFiles/testlibs.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/testlibs.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/testlibs.dir/flags.make

lib/CMakeFiles/testlibs.dir/test.cpp.o: lib/CMakeFiles/testlibs.dir/flags.make
lib/CMakeFiles/testlibs.dir/test.cpp.o: /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/lib/test.cpp
lib/CMakeFiles/testlibs.dir/test.cpp.o: lib/CMakeFiles/testlibs.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/testlibs.dir/test.cpp.o"
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/build/lib && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/testlibs.dir/test.cpp.o -MF CMakeFiles/testlibs.dir/test.cpp.o.d -o CMakeFiles/testlibs.dir/test.cpp.o -c /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/lib/test.cpp

lib/CMakeFiles/testlibs.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testlibs.dir/test.cpp.i"
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/build/lib && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/lib/test.cpp > CMakeFiles/testlibs.dir/test.cpp.i

lib/CMakeFiles/testlibs.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testlibs.dir/test.cpp.s"
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/build/lib && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/lib/test.cpp -o CMakeFiles/testlibs.dir/test.cpp.s

# Object files for target testlibs
testlibs_OBJECTS = \
"CMakeFiles/testlibs.dir/test.cpp.o"

# External object files for target testlibs
testlibs_EXTERNAL_OBJECTS =

lib/libtestlibs.dylib: lib/CMakeFiles/testlibs.dir/test.cpp.o
lib/libtestlibs.dylib: lib/CMakeFiles/testlibs.dir/build.make
lib/libtestlibs.dylib: lib/libassign.1.0.dylib
lib/libtestlibs.dylib: lib/CMakeFiles/testlibs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libtestlibs.dylib"
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testlibs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/testlibs.dir/build: lib/libtestlibs.dylib
.PHONY : lib/CMakeFiles/testlibs.dir/build

lib/CMakeFiles/testlibs.dir/clean:
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/testlibs.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/testlibs.dir/clean

lib/CMakeFiles/testlibs.dir/depend:
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/lib /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/build /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/build/lib /Users/kcl/Documents/Cpp_Projects/notepp/exp/06-eigen/build/lib/CMakeFiles/testlibs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/testlibs.dir/depend

