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
CMAKE_SOURCE_DIR = /Users/kcl/Documents/Cpp_Projects/notepp/exp/16-ssl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/kcl/Documents/Cpp_Projects/notepp/exp/16-ssl/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/encrypt.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/CMakeFiles/encrypt.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/encrypt.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/encrypt.dir/flags.make

lib/CMakeFiles/encrypt.dir/encrypt.cpp.o: lib/CMakeFiles/encrypt.dir/flags.make
lib/CMakeFiles/encrypt.dir/encrypt.cpp.o: /Users/kcl/Documents/Cpp_Projects/notepp/exp/16-ssl/lib/encrypt.cpp
lib/CMakeFiles/encrypt.dir/encrypt.cpp.o: lib/CMakeFiles/encrypt.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kcl/Documents/Cpp_Projects/notepp/exp/16-ssl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/encrypt.dir/encrypt.cpp.o"
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/16-ssl/build/lib && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/encrypt.dir/encrypt.cpp.o -MF CMakeFiles/encrypt.dir/encrypt.cpp.o.d -o CMakeFiles/encrypt.dir/encrypt.cpp.o -c /Users/kcl/Documents/Cpp_Projects/notepp/exp/16-ssl/lib/encrypt.cpp

lib/CMakeFiles/encrypt.dir/encrypt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/encrypt.dir/encrypt.cpp.i"
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/16-ssl/build/lib && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kcl/Documents/Cpp_Projects/notepp/exp/16-ssl/lib/encrypt.cpp > CMakeFiles/encrypt.dir/encrypt.cpp.i

lib/CMakeFiles/encrypt.dir/encrypt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/encrypt.dir/encrypt.cpp.s"
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/16-ssl/build/lib && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kcl/Documents/Cpp_Projects/notepp/exp/16-ssl/lib/encrypt.cpp -o CMakeFiles/encrypt.dir/encrypt.cpp.s

# Object files for target encrypt
encrypt_OBJECTS = \
"CMakeFiles/encrypt.dir/encrypt.cpp.o"

# External object files for target encrypt
encrypt_EXTERNAL_OBJECTS =

lib/libencrypt.1.0.dylib: lib/CMakeFiles/encrypt.dir/encrypt.cpp.o
lib/libencrypt.1.0.dylib: lib/CMakeFiles/encrypt.dir/build.make
lib/libencrypt.1.0.dylib: lib/CMakeFiles/encrypt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kcl/Documents/Cpp_Projects/notepp/exp/16-ssl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libencrypt.dylib"
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/16-ssl/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/encrypt.dir/link.txt --verbose=$(VERBOSE)
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/16-ssl/build/lib && $(CMAKE_COMMAND) -E cmake_symlink_library libencrypt.1.0.dylib libencrypt.1.dylib libencrypt.dylib

lib/libencrypt.1.dylib: lib/libencrypt.1.0.dylib
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libencrypt.1.dylib

lib/libencrypt.dylib: lib/libencrypt.1.0.dylib
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libencrypt.dylib

# Rule to build all files generated by this target.
lib/CMakeFiles/encrypt.dir/build: lib/libencrypt.dylib
.PHONY : lib/CMakeFiles/encrypt.dir/build

lib/CMakeFiles/encrypt.dir/clean:
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/16-ssl/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/encrypt.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/encrypt.dir/clean

lib/CMakeFiles/encrypt.dir/depend:
	cd /Users/kcl/Documents/Cpp_Projects/notepp/exp/16-ssl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kcl/Documents/Cpp_Projects/notepp/exp/16-ssl /Users/kcl/Documents/Cpp_Projects/notepp/exp/16-ssl/lib /Users/kcl/Documents/Cpp_Projects/notepp/exp/16-ssl/build /Users/kcl/Documents/Cpp_Projects/notepp/exp/16-ssl/build/lib /Users/kcl/Documents/Cpp_Projects/notepp/exp/16-ssl/build/lib/CMakeFiles/encrypt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/encrypt.dir/depend

