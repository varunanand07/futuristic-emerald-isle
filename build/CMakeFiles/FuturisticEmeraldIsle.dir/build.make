# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/varunanand/futuristic-emerald-isle

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/varunanand/futuristic-emerald-isle/build

# Include any dependencies generated for this target.
include CMakeFiles/FuturisticEmeraldIsle.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/FuturisticEmeraldIsle.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/FuturisticEmeraldIsle.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FuturisticEmeraldIsle.dir/flags.make

CMakeFiles/FuturisticEmeraldIsle.dir/src/main.cpp.o: CMakeFiles/FuturisticEmeraldIsle.dir/flags.make
CMakeFiles/FuturisticEmeraldIsle.dir/src/main.cpp.o: /Users/varunanand/futuristic-emerald-isle/src/main.cpp
CMakeFiles/FuturisticEmeraldIsle.dir/src/main.cpp.o: CMakeFiles/FuturisticEmeraldIsle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/varunanand/futuristic-emerald-isle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FuturisticEmeraldIsle.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/FuturisticEmeraldIsle.dir/src/main.cpp.o -MF CMakeFiles/FuturisticEmeraldIsle.dir/src/main.cpp.o.d -o CMakeFiles/FuturisticEmeraldIsle.dir/src/main.cpp.o -c /Users/varunanand/futuristic-emerald-isle/src/main.cpp

CMakeFiles/FuturisticEmeraldIsle.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/FuturisticEmeraldIsle.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/varunanand/futuristic-emerald-isle/src/main.cpp > CMakeFiles/FuturisticEmeraldIsle.dir/src/main.cpp.i

CMakeFiles/FuturisticEmeraldIsle.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/FuturisticEmeraldIsle.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/varunanand/futuristic-emerald-isle/src/main.cpp -o CMakeFiles/FuturisticEmeraldIsle.dir/src/main.cpp.s

CMakeFiles/FuturisticEmeraldIsle.dir/src/shader.cpp.o: CMakeFiles/FuturisticEmeraldIsle.dir/flags.make
CMakeFiles/FuturisticEmeraldIsle.dir/src/shader.cpp.o: /Users/varunanand/futuristic-emerald-isle/src/shader.cpp
CMakeFiles/FuturisticEmeraldIsle.dir/src/shader.cpp.o: CMakeFiles/FuturisticEmeraldIsle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/varunanand/futuristic-emerald-isle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/FuturisticEmeraldIsle.dir/src/shader.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/FuturisticEmeraldIsle.dir/src/shader.cpp.o -MF CMakeFiles/FuturisticEmeraldIsle.dir/src/shader.cpp.o.d -o CMakeFiles/FuturisticEmeraldIsle.dir/src/shader.cpp.o -c /Users/varunanand/futuristic-emerald-isle/src/shader.cpp

CMakeFiles/FuturisticEmeraldIsle.dir/src/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/FuturisticEmeraldIsle.dir/src/shader.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/varunanand/futuristic-emerald-isle/src/shader.cpp > CMakeFiles/FuturisticEmeraldIsle.dir/src/shader.cpp.i

CMakeFiles/FuturisticEmeraldIsle.dir/src/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/FuturisticEmeraldIsle.dir/src/shader.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/varunanand/futuristic-emerald-isle/src/shader.cpp -o CMakeFiles/FuturisticEmeraldIsle.dir/src/shader.cpp.s

# Object files for target FuturisticEmeraldIsle
FuturisticEmeraldIsle_OBJECTS = \
"CMakeFiles/FuturisticEmeraldIsle.dir/src/main.cpp.o" \
"CMakeFiles/FuturisticEmeraldIsle.dir/src/shader.cpp.o"

# External object files for target FuturisticEmeraldIsle
FuturisticEmeraldIsle_EXTERNAL_OBJECTS =

FuturisticEmeraldIsle: CMakeFiles/FuturisticEmeraldIsle.dir/src/main.cpp.o
FuturisticEmeraldIsle: CMakeFiles/FuturisticEmeraldIsle.dir/src/shader.cpp.o
FuturisticEmeraldIsle: CMakeFiles/FuturisticEmeraldIsle.dir/build.make
FuturisticEmeraldIsle: /opt/homebrew/lib/libGLEW.2.2.0.dylib
FuturisticEmeraldIsle: /opt/homebrew/lib/libglfw.3.4.dylib
FuturisticEmeraldIsle: CMakeFiles/FuturisticEmeraldIsle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/varunanand/futuristic-emerald-isle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable FuturisticEmeraldIsle"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FuturisticEmeraldIsle.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FuturisticEmeraldIsle.dir/build: FuturisticEmeraldIsle
.PHONY : CMakeFiles/FuturisticEmeraldIsle.dir/build

CMakeFiles/FuturisticEmeraldIsle.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FuturisticEmeraldIsle.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FuturisticEmeraldIsle.dir/clean

CMakeFiles/FuturisticEmeraldIsle.dir/depend:
	cd /Users/varunanand/futuristic-emerald-isle/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/varunanand/futuristic-emerald-isle /Users/varunanand/futuristic-emerald-isle /Users/varunanand/futuristic-emerald-isle/build /Users/varunanand/futuristic-emerald-isle/build /Users/varunanand/futuristic-emerald-isle/build/CMakeFiles/FuturisticEmeraldIsle.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/FuturisticEmeraldIsle.dir/depend

