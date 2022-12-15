#!/bin/sh
make -C /Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib -f /Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/CMakeScripts/say-hello_postBuildPhase.make$CONFIGURATION OBJDIR=$(basename "$OBJECT_FILE_DIR_normal") all
