# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.6/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.6/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/zyu/Desktop/Projet/PSCR-TME

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/zyu/Desktop/Projet/PSCR-TME

# Include any dependencies generated for this target.
include CMakeFiles/TME2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TME2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TME2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TME2.dir/flags.make

CMakeFiles/TME2.dir/TME2/main.cpp.o: CMakeFiles/TME2.dir/flags.make
CMakeFiles/TME2.dir/TME2/main.cpp.o: TME2/main.cpp
CMakeFiles/TME2.dir/TME2/main.cpp.o: CMakeFiles/TME2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/zyu/Desktop/Projet/PSCR-TME/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TME2.dir/TME2/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TME2.dir/TME2/main.cpp.o -MF CMakeFiles/TME2.dir/TME2/main.cpp.o.d -o CMakeFiles/TME2.dir/TME2/main.cpp.o -c /Users/zyu/Desktop/Projet/PSCR-TME/TME2/main.cpp

CMakeFiles/TME2.dir/TME2/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TME2.dir/TME2/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zyu/Desktop/Projet/PSCR-TME/TME2/main.cpp > CMakeFiles/TME2.dir/TME2/main.cpp.i

CMakeFiles/TME2.dir/TME2/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TME2.dir/TME2/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zyu/Desktop/Projet/PSCR-TME/TME2/main.cpp -o CMakeFiles/TME2.dir/TME2/main.cpp.s

# Object files for target TME2
TME2_OBJECTS = \
"CMakeFiles/TME2.dir/TME2/main.cpp.o"

# External object files for target TME2
TME2_EXTERNAL_OBJECTS =

TME2: CMakeFiles/TME2.dir/TME2/main.cpp.o
TME2: CMakeFiles/TME2.dir/build.make
TME2: CMakeFiles/TME2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/zyu/Desktop/Projet/PSCR-TME/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TME2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TME2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TME2.dir/build: TME2
.PHONY : CMakeFiles/TME2.dir/build

CMakeFiles/TME2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TME2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TME2.dir/clean

CMakeFiles/TME2.dir/depend:
	cd /Users/zyu/Desktop/Projet/PSCR-TME && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/zyu/Desktop/Projet/PSCR-TME /Users/zyu/Desktop/Projet/PSCR-TME /Users/zyu/Desktop/Projet/PSCR-TME /Users/zyu/Desktop/Projet/PSCR-TME /Users/zyu/Desktop/Projet/PSCR-TME/CMakeFiles/TME2.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/TME2.dir/depend

