# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.21

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\dev\soket_programing\server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\dev\soket_programing\server\build

# Include any dependencies generated for this target.
include CMakeFiles/socket_programing.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/socket_programing.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/socket_programing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/socket_programing.dir/flags.make

CMakeFiles/socket_programing.dir/src/day06_01.c.obj: CMakeFiles/socket_programing.dir/flags.make
CMakeFiles/socket_programing.dir/src/day06_01.c.obj: ../src/day06_01.c
CMakeFiles/socket_programing.dir/src/day06_01.c.obj: CMakeFiles/socket_programing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\dev\soket_programing\server\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/socket_programing.dir/src/day06_01.c.obj"
	C:\MinGW\bin\mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/socket_programing.dir/src/day06_01.c.obj -MF CMakeFiles\socket_programing.dir\src\day06_01.c.obj.d -o CMakeFiles\socket_programing.dir\src\day06_01.c.obj -c C:\dev\soket_programing\server\src\day06_01.c

CMakeFiles/socket_programing.dir/src/day06_01.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/socket_programing.dir/src/day06_01.c.i"
	C:\MinGW\bin\mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\dev\soket_programing\server\src\day06_01.c > CMakeFiles\socket_programing.dir\src\day06_01.c.i

CMakeFiles/socket_programing.dir/src/day06_01.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/socket_programing.dir/src/day06_01.c.s"
	C:\MinGW\bin\mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\dev\soket_programing\server\src\day06_01.c -o CMakeFiles\socket_programing.dir\src\day06_01.c.s

# Object files for target socket_programing
socket_programing_OBJECTS = \
"CMakeFiles/socket_programing.dir/src/day06_01.c.obj"

# External object files for target socket_programing
socket_programing_EXTERNAL_OBJECTS =

socket_programing.exe: CMakeFiles/socket_programing.dir/src/day06_01.c.obj
socket_programing.exe: CMakeFiles/socket_programing.dir/build.make
socket_programing.exe: CMakeFiles/socket_programing.dir/linklibs.rsp
socket_programing.exe: CMakeFiles/socket_programing.dir/objects1.rsp
socket_programing.exe: CMakeFiles/socket_programing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\dev\soket_programing\server\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable socket_programing.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\socket_programing.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/socket_programing.dir/build: socket_programing.exe
.PHONY : CMakeFiles/socket_programing.dir/build

CMakeFiles/socket_programing.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\socket_programing.dir\cmake_clean.cmake
.PHONY : CMakeFiles/socket_programing.dir/clean

CMakeFiles/socket_programing.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\dev\soket_programing\server C:\dev\soket_programing\server C:\dev\soket_programing\server\build C:\dev\soket_programing\server\build C:\dev\soket_programing\server\build\CMakeFiles\socket_programing.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/socket_programing.dir/depend
