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
CMAKE_COMMAND = /home/ubt/.local/lib/python3.8/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/ubt/.local/lib/python3.8/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubt/Documents/algorithm/C++/notepp/exp/02-cmake-level2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubt/Documents/algorithm/C++/notepp/exp/02-cmake-level2/build

# Include any dependencies generated for this target.
include CMakeFiles/exeName.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/exeName.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/exeName.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/exeName.dir/flags.make

CMakeFiles/exeName.dir/main.cpp.o: CMakeFiles/exeName.dir/flags.make
CMakeFiles/exeName.dir/main.cpp.o: /home/ubt/Documents/algorithm/C++/notepp/exp/02-cmake-level2/main.cpp
CMakeFiles/exeName.dir/main.cpp.o: CMakeFiles/exeName.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubt/Documents/algorithm/C++/notepp/exp/02-cmake-level2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/exeName.dir/main.cpp.o"
	/home/thomas/rv1126/repo_new/buildroot/output/rockchip_rv1126_rv1109/host/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exeName.dir/main.cpp.o -MF CMakeFiles/exeName.dir/main.cpp.o.d -o CMakeFiles/exeName.dir/main.cpp.o -c /home/ubt/Documents/algorithm/C++/notepp/exp/02-cmake-level2/main.cpp

CMakeFiles/exeName.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exeName.dir/main.cpp.i"
	/home/thomas/rv1126/repo_new/buildroot/output/rockchip_rv1126_rv1109/host/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubt/Documents/algorithm/C++/notepp/exp/02-cmake-level2/main.cpp > CMakeFiles/exeName.dir/main.cpp.i

CMakeFiles/exeName.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exeName.dir/main.cpp.s"
	/home/thomas/rv1126/repo_new/buildroot/output/rockchip_rv1126_rv1109/host/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubt/Documents/algorithm/C++/notepp/exp/02-cmake-level2/main.cpp -o CMakeFiles/exeName.dir/main.cpp.s

# Object files for target exeName
exeName_OBJECTS = \
"CMakeFiles/exeName.dir/main.cpp.o"

# External object files for target exeName
exeName_EXTERNAL_OBJECTS =

exeName: CMakeFiles/exeName.dir/main.cpp.o
exeName: CMakeFiles/exeName.dir/build.make
exeName: liblib-name.a
exeName: CMakeFiles/exeName.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubt/Documents/algorithm/C++/notepp/exp/02-cmake-level2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable exeName"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exeName.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/exeName.dir/build: exeName
.PHONY : CMakeFiles/exeName.dir/build

CMakeFiles/exeName.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/exeName.dir/cmake_clean.cmake
.PHONY : CMakeFiles/exeName.dir/clean

CMakeFiles/exeName.dir/depend:
	cd /home/ubt/Documents/algorithm/C++/notepp/exp/02-cmake-level2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubt/Documents/algorithm/C++/notepp/exp/02-cmake-level2 /home/ubt/Documents/algorithm/C++/notepp/exp/02-cmake-level2 /home/ubt/Documents/algorithm/C++/notepp/exp/02-cmake-level2/build /home/ubt/Documents/algorithm/C++/notepp/exp/02-cmake-level2/build /home/ubt/Documents/algorithm/C++/notepp/exp/02-cmake-level2/build/CMakeFiles/exeName.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/exeName.dir/depend

