# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /mnt/c/Users/riosv/Documents/proyecto3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/riosv/Documents/proyecto3/buil

# Include any dependencies generated for this target.
include external/glad/CMakeFiles/glad.dir/depend.make

# Include the progress variables for this target.
include external/glad/CMakeFiles/glad.dir/progress.make

# Include the compile flags for this target's objects.
include external/glad/CMakeFiles/glad.dir/flags.make

external/glad/CMakeFiles/glad.dir/src/glad.c.o: external/glad/CMakeFiles/glad.dir/flags.make
external/glad/CMakeFiles/glad.dir/src/glad.c.o: ../external/glad/src/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/riosv/Documents/proyecto3/buil/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object external/glad/CMakeFiles/glad.dir/src/glad.c.o"
	cd /mnt/c/Users/riosv/Documents/proyecto3/buil/external/glad && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glad.dir/src/glad.c.o   -c /mnt/c/Users/riosv/Documents/proyecto3/external/glad/src/glad.c

external/glad/CMakeFiles/glad.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glad.dir/src/glad.c.i"
	cd /mnt/c/Users/riosv/Documents/proyecto3/buil/external/glad && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/riosv/Documents/proyecto3/external/glad/src/glad.c > CMakeFiles/glad.dir/src/glad.c.i

external/glad/CMakeFiles/glad.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glad.dir/src/glad.c.s"
	cd /mnt/c/Users/riosv/Documents/proyecto3/buil/external/glad && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/riosv/Documents/proyecto3/external/glad/src/glad.c -o CMakeFiles/glad.dir/src/glad.c.s

# Object files for target glad
glad_OBJECTS = \
"CMakeFiles/glad.dir/src/glad.c.o"

# External object files for target glad
glad_EXTERNAL_OBJECTS =

external/glad/libglad.a: external/glad/CMakeFiles/glad.dir/src/glad.c.o
external/glad/libglad.a: external/glad/CMakeFiles/glad.dir/build.make
external/glad/libglad.a: external/glad/CMakeFiles/glad.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/riosv/Documents/proyecto3/buil/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libglad.a"
	cd /mnt/c/Users/riosv/Documents/proyecto3/buil/external/glad && $(CMAKE_COMMAND) -P CMakeFiles/glad.dir/cmake_clean_target.cmake
	cd /mnt/c/Users/riosv/Documents/proyecto3/buil/external/glad && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glad.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/glad/CMakeFiles/glad.dir/build: external/glad/libglad.a

.PHONY : external/glad/CMakeFiles/glad.dir/build

external/glad/CMakeFiles/glad.dir/clean:
	cd /mnt/c/Users/riosv/Documents/proyecto3/buil/external/glad && $(CMAKE_COMMAND) -P CMakeFiles/glad.dir/cmake_clean.cmake
.PHONY : external/glad/CMakeFiles/glad.dir/clean

external/glad/CMakeFiles/glad.dir/depend:
	cd /mnt/c/Users/riosv/Documents/proyecto3/buil && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/riosv/Documents/proyecto3 /mnt/c/Users/riosv/Documents/proyecto3/external/glad /mnt/c/Users/riosv/Documents/proyecto3/buil /mnt/c/Users/riosv/Documents/proyecto3/buil/external/glad /mnt/c/Users/riosv/Documents/proyecto3/buil/external/glad/CMakeFiles/glad.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/glad/CMakeFiles/glad.dir/depend

