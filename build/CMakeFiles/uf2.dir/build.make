# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/student/facultate/PM/proiect_esp32c6/esp-idf/hello-world

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/student/facultate/PM/proiect_esp32c6/esp-idf/hello-world/build

# Utility rule file for uf2.

# Include any custom commands dependencies for this target.
include CMakeFiles/uf2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/uf2.dir/progress.make

CMakeFiles/uf2:
	/usr/bin/cmake -D IDF_PATH=/home/student/facultate/PM/proiect_esp32c6/esp-idf -D "UF2_CMD=/home/student/.espressif/python_env/idf6.0_py3.10_env/bin/python;/home/student/facultate/PM/proiect_esp32c6/esp-idf/tools/mkuf2.py;write;--chip;esp32c6" -D "UF2_ARGS=--json;/home/student/facultate/PM/proiect_esp32c6/esp-idf/hello-world/build/flasher_args.json;-o;/home/student/facultate/PM/proiect_esp32c6/esp-idf/hello-world/build/uf2.bin" -P /home/student/facultate/PM/proiect_esp32c6/esp-idf/tools/cmake/run_uf2_cmds.cmake

uf2: CMakeFiles/uf2
uf2: CMakeFiles/uf2.dir/build.make
.PHONY : uf2

# Rule to build all files generated by this target.
CMakeFiles/uf2.dir/build: uf2
.PHONY : CMakeFiles/uf2.dir/build

CMakeFiles/uf2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/uf2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/uf2.dir/clean

CMakeFiles/uf2.dir/depend:
	cd /home/student/facultate/PM/proiect_esp32c6/esp-idf/hello-world/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/student/facultate/PM/proiect_esp32c6/esp-idf/hello-world /home/student/facultate/PM/proiect_esp32c6/esp-idf/hello-world /home/student/facultate/PM/proiect_esp32c6/esp-idf/hello-world/build /home/student/facultate/PM/proiect_esp32c6/esp-idf/hello-world/build /home/student/facultate/PM/proiect_esp32c6/esp-idf/hello-world/build/CMakeFiles/uf2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/uf2.dir/depend

