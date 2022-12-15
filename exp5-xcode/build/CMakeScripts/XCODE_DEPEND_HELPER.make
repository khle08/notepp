# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.exeName.Debug:
PostBuild.say-hello.Debug: /Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/bin/Debug/exeName
/Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/bin/Debug/exeName:\
	/Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/Debug/libsay-hello.1.2.dylib
	/bin/rm -f /Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/bin/Debug/exeName


PostBuild.say-hello.Debug:
/Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/Debug/libsay-hello.dylib:
	/bin/rm -f /Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/Debug/libsay-hello.dylib


PostBuild.say-hello_static.Debug:
/Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/Debug/libsay-hello.a:
	/bin/rm -f /Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/Debug/libsay-hello.a


PostBuild.exeName.Release:
PostBuild.say-hello.Release: /Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/bin/Release/exeName
/Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/bin/Release/exeName:\
	/Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/Release/libsay-hello.1.2.dylib
	/bin/rm -f /Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/bin/Release/exeName


PostBuild.say-hello.Release:
/Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/Release/libsay-hello.dylib:
	/bin/rm -f /Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/Release/libsay-hello.dylib


PostBuild.say-hello_static.Release:
/Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/Release/libsay-hello.a:
	/bin/rm -f /Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/Release/libsay-hello.a


PostBuild.exeName.MinSizeRel:
PostBuild.say-hello.MinSizeRel: /Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/bin/MinSizeRel/exeName
/Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/bin/MinSizeRel/exeName:\
	/Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/MinSizeRel/libsay-hello.1.2.dylib
	/bin/rm -f /Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/bin/MinSizeRel/exeName


PostBuild.say-hello.MinSizeRel:
/Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/MinSizeRel/libsay-hello.dylib:
	/bin/rm -f /Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/MinSizeRel/libsay-hello.dylib


PostBuild.say-hello_static.MinSizeRel:
/Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/MinSizeRel/libsay-hello.a:
	/bin/rm -f /Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/MinSizeRel/libsay-hello.a


PostBuild.exeName.RelWithDebInfo:
PostBuild.say-hello.RelWithDebInfo: /Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/bin/RelWithDebInfo/exeName
/Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/bin/RelWithDebInfo/exeName:\
	/Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/RelWithDebInfo/libsay-hello.1.2.dylib
	/bin/rm -f /Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/bin/RelWithDebInfo/exeName


PostBuild.say-hello.RelWithDebInfo:
/Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/RelWithDebInfo/libsay-hello.dylib:
	/bin/rm -f /Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/RelWithDebInfo/libsay-hello.dylib


PostBuild.say-hello_static.RelWithDebInfo:
/Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/RelWithDebInfo/libsay-hello.a:
	/bin/rm -f /Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/RelWithDebInfo/libsay-hello.a




# For each target create a dummy ruleso the target does not have to exist
/Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/Debug/libsay-hello.1.2.dylib:
/Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/MinSizeRel/libsay-hello.1.2.dylib:
/Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/RelWithDebInfo/libsay-hello.1.2.dylib:
/Users/kcl/Documents/Cpp_Projects/cpp_notes/exp5-xcode/build/lib/Release/libsay-hello.1.2.dylib:
