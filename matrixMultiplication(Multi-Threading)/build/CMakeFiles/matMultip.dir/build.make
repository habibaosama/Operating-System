# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/habiba/Desktop/matrixMultiplication

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/habiba/Desktop/matrixMultiplication/build

# Include any dependencies generated for this target.
include CMakeFiles/matMultip.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/matMultip.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/matMultip.dir/flags.make

CMakeFiles/matMultip.dir/matMultip.c.o: CMakeFiles/matMultip.dir/flags.make
CMakeFiles/matMultip.dir/matMultip.c.o: ../matMultip.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/habiba/Desktop/matrixMultiplication/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/matMultip.dir/matMultip.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/matMultip.dir/matMultip.c.o   -c /home/habiba/Desktop/matrixMultiplication/matMultip.c

CMakeFiles/matMultip.dir/matMultip.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/matMultip.dir/matMultip.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/habiba/Desktop/matrixMultiplication/matMultip.c > CMakeFiles/matMultip.dir/matMultip.c.i

CMakeFiles/matMultip.dir/matMultip.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/matMultip.dir/matMultip.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/habiba/Desktop/matrixMultiplication/matMultip.c -o CMakeFiles/matMultip.dir/matMultip.c.s

CMakeFiles/matMultip.dir/matMultip.c.o.requires:

.PHONY : CMakeFiles/matMultip.dir/matMultip.c.o.requires

CMakeFiles/matMultip.dir/matMultip.c.o.provides: CMakeFiles/matMultip.dir/matMultip.c.o.requires
	$(MAKE) -f CMakeFiles/matMultip.dir/build.make CMakeFiles/matMultip.dir/matMultip.c.o.provides.build
.PHONY : CMakeFiles/matMultip.dir/matMultip.c.o.provides

CMakeFiles/matMultip.dir/matMultip.c.o.provides.build: CMakeFiles/matMultip.dir/matMultip.c.o


# Object files for target matMultip
matMultip_OBJECTS = \
"CMakeFiles/matMultip.dir/matMultip.c.o"

# External object files for target matMultip
matMultip_EXTERNAL_OBJECTS =

matMultip: CMakeFiles/matMultip.dir/matMultip.c.o
matMultip: CMakeFiles/matMultip.dir/build.make
matMultip: CMakeFiles/matMultip.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/habiba/Desktop/matrixMultiplication/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable matMultip"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/matMultip.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/matMultip.dir/build: matMultip

.PHONY : CMakeFiles/matMultip.dir/build

CMakeFiles/matMultip.dir/requires: CMakeFiles/matMultip.dir/matMultip.c.o.requires

.PHONY : CMakeFiles/matMultip.dir/requires

CMakeFiles/matMultip.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/matMultip.dir/cmake_clean.cmake
.PHONY : CMakeFiles/matMultip.dir/clean

CMakeFiles/matMultip.dir/depend:
	cd /home/habiba/Desktop/matrixMultiplication/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/habiba/Desktop/matrixMultiplication /home/habiba/Desktop/matrixMultiplication /home/habiba/Desktop/matrixMultiplication/build /home/habiba/Desktop/matrixMultiplication/build /home/habiba/Desktop/matrixMultiplication/build/CMakeFiles/matMultip.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/matMultip.dir/depend
