#!/bin/sh
make -C /Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build -f /Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/CMakeScripts/install_postBuildPhase.make$CONFIGURATION OBJDIR=$(basename "$OBJECT_FILE_DIR_normal") all
