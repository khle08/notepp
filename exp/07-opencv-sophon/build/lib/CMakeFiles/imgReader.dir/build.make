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
CMAKE_SOURCE_DIR = /home/ubt/Documents/algorithm/C++/notepp/exp/07-opencv-sophon

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubt/Documents/algorithm/C++/notepp/exp/07-opencv-sophon/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/imgReader.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/CMakeFiles/imgReader.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/imgReader.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/imgReader.dir/flags.make

lib/CMakeFiles/imgReader.dir/imgReader.cpp.o: lib/CMakeFiles/imgReader.dir/flags.make
lib/CMakeFiles/imgReader.dir/imgReader.cpp.o: /home/ubt/Documents/algorithm/C++/notepp/exp/07-opencv-sophon/lib/imgReader.cpp
lib/CMakeFiles/imgReader.dir/imgReader.cpp.o: lib/CMakeFiles/imgReader.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubt/Documents/algorithm/C++/notepp/exp/07-opencv-sophon/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/imgReader.dir/imgReader.cpp.o"
	cd /home/ubt/Documents/algorithm/C++/notepp/exp/07-opencv-sophon/build/lib && /usr/bin/aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/imgReader.dir/imgReader.cpp.o -MF CMakeFiles/imgReader.dir/imgReader.cpp.o.d -o CMakeFiles/imgReader.dir/imgReader.cpp.o -c /home/ubt/Documents/algorithm/C++/notepp/exp/07-opencv-sophon/lib/imgReader.cpp

lib/CMakeFiles/imgReader.dir/imgReader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgReader.dir/imgReader.cpp.i"
	cd /home/ubt/Documents/algorithm/C++/notepp/exp/07-opencv-sophon/build/lib && /usr/bin/aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubt/Documents/algorithm/C++/notepp/exp/07-opencv-sophon/lib/imgReader.cpp > CMakeFiles/imgReader.dir/imgReader.cpp.i

lib/CMakeFiles/imgReader.dir/imgReader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgReader.dir/imgReader.cpp.s"
	cd /home/ubt/Documents/algorithm/C++/notepp/exp/07-opencv-sophon/build/lib && /usr/bin/aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubt/Documents/algorithm/C++/notepp/exp/07-opencv-sophon/lib/imgReader.cpp -o CMakeFiles/imgReader.dir/imgReader.cpp.s

# Object files for target imgReader
imgReader_OBJECTS = \
"CMakeFiles/imgReader.dir/imgReader.cpp.o"

# External object files for target imgReader
imgReader_EXTERNAL_OBJECTS =

lib/libimgReader.so.1.0: lib/CMakeFiles/imgReader.dir/imgReader.cpp.o
lib/libimgReader.so.1.0: lib/CMakeFiles/imgReader.dir/build.make
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libavcodec.a
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libavdevice.a
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libavfilter.a
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libavformat.a
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libavutil.a
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libbmcv.a
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libbmodel.a
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libbmrt.a
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libswresample.a
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libswscale.a
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libvpp.a
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libyuv.a
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libavcodec.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libavdevice.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libavfilter.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libavformat.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libavutil.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libbmcv.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libbmion.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libbmjpuapi.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libbmjpulite.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libbmlib.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libbmrt.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libbmvideo.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libbmvppapi.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libbmvpuapi.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libbmvpulite.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libcpuop.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libopencv_calib3d.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libopencv_core.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libopencv_dnn.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libopencv_features2d.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libopencv_flann.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libopencv_freetype.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libopencv_gapi.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libopencv_highgui.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libopencv_imgcodecs.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libopencv_imgproc.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libopencv_ml.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libopencv_objdetect.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libopencv_photo.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libopencv_stitching.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libopencv_video.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libopencv_videoio.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libswresample.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libswscale.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libusercpu.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libvideo_bm.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libvpp.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libvpp_cmodel.so
lib/libimgReader.so.1.0: /home/ubt/Documents/compilation/Sophon-SDK-24.04.01/soc-sdk/lib/libyuv.so
lib/libimgReader.so.1.0: lib/CMakeFiles/imgReader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubt/Documents/algorithm/C++/notepp/exp/07-opencv-sophon/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libimgReader.so"
	cd /home/ubt/Documents/algorithm/C++/notepp/exp/07-opencv-sophon/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imgReader.dir/link.txt --verbose=$(VERBOSE)
	cd /home/ubt/Documents/algorithm/C++/notepp/exp/07-opencv-sophon/build/lib && $(CMAKE_COMMAND) -E cmake_symlink_library libimgReader.so.1.0 libimgReader.so.1 libimgReader.so

lib/libimgReader.so.1: lib/libimgReader.so.1.0
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libimgReader.so.1

lib/libimgReader.so: lib/libimgReader.so.1.0
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libimgReader.so

# Rule to build all files generated by this target.
lib/CMakeFiles/imgReader.dir/build: lib/libimgReader.so
.PHONY : lib/CMakeFiles/imgReader.dir/build

lib/CMakeFiles/imgReader.dir/clean:
	cd /home/ubt/Documents/algorithm/C++/notepp/exp/07-opencv-sophon/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/imgReader.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/imgReader.dir/clean

lib/CMakeFiles/imgReader.dir/depend:
	cd /home/ubt/Documents/algorithm/C++/notepp/exp/07-opencv-sophon/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubt/Documents/algorithm/C++/notepp/exp/07-opencv-sophon /home/ubt/Documents/algorithm/C++/notepp/exp/07-opencv-sophon/lib /home/ubt/Documents/algorithm/C++/notepp/exp/07-opencv-sophon/build /home/ubt/Documents/algorithm/C++/notepp/exp/07-opencv-sophon/build/lib /home/ubt/Documents/algorithm/C++/notepp/exp/07-opencv-sophon/build/lib/CMakeFiles/imgReader.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/imgReader.dir/depend

