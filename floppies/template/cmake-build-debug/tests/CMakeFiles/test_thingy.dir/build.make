# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /home/luc/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/192.5728.100/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/luc/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/192.5728.100/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/cmake-build-debug

# Include any dependencies generated for this target.
include tests/CMakeFiles/test_thingy.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_thingy.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_thingy.dir/flags.make

tests/CMakeFiles/test_thingy.dir/main.c.o: tests/CMakeFiles/test_thingy.dir/flags.make
tests/CMakeFiles/test_thingy.dir/main.c.o: ../tests/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/test_thingy.dir/main.c.o"
	cd /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/cmake-build-debug/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_thingy.dir/main.c.o   -c /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/tests/main.c

tests/CMakeFiles/test_thingy.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_thingy.dir/main.c.i"
	cd /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/cmake-build-debug/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/tests/main.c > CMakeFiles/test_thingy.dir/main.c.i

tests/CMakeFiles/test_thingy.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_thingy.dir/main.c.s"
	cd /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/cmake-build-debug/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/tests/main.c -o CMakeFiles/test_thingy.dir/main.c.s

tests/CMakeFiles/test_thingy.dir/suites/add.c.o: tests/CMakeFiles/test_thingy.dir/flags.make
tests/CMakeFiles/test_thingy.dir/suites/add.c.o: ../tests/suites/add.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/test_thingy.dir/suites/add.c.o"
	cd /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/cmake-build-debug/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_thingy.dir/suites/add.c.o   -c /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/tests/suites/add.c

tests/CMakeFiles/test_thingy.dir/suites/add.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_thingy.dir/suites/add.c.i"
	cd /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/cmake-build-debug/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/tests/suites/add.c > CMakeFiles/test_thingy.dir/suites/add.c.i

tests/CMakeFiles/test_thingy.dir/suites/add.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_thingy.dir/suites/add.c.s"
	cd /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/cmake-build-debug/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/tests/suites/add.c -o CMakeFiles/test_thingy.dir/suites/add.c.s

# Object files for target test_thingy
test_thingy_OBJECTS = \
"CMakeFiles/test_thingy.dir/main.c.o" \
"CMakeFiles/test_thingy.dir/suites/add.c.o"

# External object files for target test_thingy
test_thingy_EXTERNAL_OBJECTS =

tests/test_thingy: tests/CMakeFiles/test_thingy.dir/main.c.o
tests/test_thingy: tests/CMakeFiles/test_thingy.dir/suites/add.c.o
tests/test_thingy: tests/CMakeFiles/test_thingy.dir/build.make
tests/test_thingy: source/library/libthingylib.a
tests/test_thingy: tests/CMakeFiles/test_thingy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable test_thingy"
	cd /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/cmake-build-debug/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_thingy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_thingy.dir/build: tests/test_thingy

.PHONY : tests/CMakeFiles/test_thingy.dir/build

tests/CMakeFiles/test_thingy.dir/clean:
	cd /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/cmake-build-debug/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_thingy.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_thingy.dir/clean

tests/CMakeFiles/test_thingy.dir/depend:
	cd /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/tests /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/cmake-build-debug /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/cmake-build-debug/tests /home/luc/Documents/Work/Side_Projects/Floppy_Challenge/Repo/floppies/thingy/cmake-build-debug/tests/CMakeFiles/test_thingy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/test_thingy.dir/depend

