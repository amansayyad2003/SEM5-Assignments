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
CMAKE_SOURCE_DIR = /home/aman2003/SEM5/SE/Assignments/CMake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aman2003/SEM5/SE/Assignments/CMake/build

# Include any dependencies generated for this target.
include mylib/CMakeFiles/calci.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include mylib/CMakeFiles/calci.dir/compiler_depend.make

# Include the progress variables for this target.
include mylib/CMakeFiles/calci.dir/progress.make

# Include the compile flags for this target's objects.
include mylib/CMakeFiles/calci.dir/flags.make

mylib/CMakeFiles/calci.dir/calci.cpp.o: mylib/CMakeFiles/calci.dir/flags.make
mylib/CMakeFiles/calci.dir/calci.cpp.o: ../mylib/calci.cpp
mylib/CMakeFiles/calci.dir/calci.cpp.o: mylib/CMakeFiles/calci.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aman2003/SEM5/SE/Assignments/CMake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object mylib/CMakeFiles/calci.dir/calci.cpp.o"
	cd /home/aman2003/SEM5/SE/Assignments/CMake/build/mylib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT mylib/CMakeFiles/calci.dir/calci.cpp.o -MF CMakeFiles/calci.dir/calci.cpp.o.d -o CMakeFiles/calci.dir/calci.cpp.o -c /home/aman2003/SEM5/SE/Assignments/CMake/mylib/calci.cpp

mylib/CMakeFiles/calci.dir/calci.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calci.dir/calci.cpp.i"
	cd /home/aman2003/SEM5/SE/Assignments/CMake/build/mylib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aman2003/SEM5/SE/Assignments/CMake/mylib/calci.cpp > CMakeFiles/calci.dir/calci.cpp.i

mylib/CMakeFiles/calci.dir/calci.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calci.dir/calci.cpp.s"
	cd /home/aman2003/SEM5/SE/Assignments/CMake/build/mylib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aman2003/SEM5/SE/Assignments/CMake/mylib/calci.cpp -o CMakeFiles/calci.dir/calci.cpp.s

# Object files for target calci
calci_OBJECTS = \
"CMakeFiles/calci.dir/calci.cpp.o"

# External object files for target calci
calci_EXTERNAL_OBJECTS =

mylib/libcalci.so: mylib/CMakeFiles/calci.dir/calci.cpp.o
mylib/libcalci.so: mylib/CMakeFiles/calci.dir/build.make
mylib/libcalci.so: mylib/CMakeFiles/calci.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aman2003/SEM5/SE/Assignments/CMake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libcalci.so"
	cd /home/aman2003/SEM5/SE/Assignments/CMake/build/mylib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/calci.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
mylib/CMakeFiles/calci.dir/build: mylib/libcalci.so
.PHONY : mylib/CMakeFiles/calci.dir/build

mylib/CMakeFiles/calci.dir/clean:
	cd /home/aman2003/SEM5/SE/Assignments/CMake/build/mylib && $(CMAKE_COMMAND) -P CMakeFiles/calci.dir/cmake_clean.cmake
.PHONY : mylib/CMakeFiles/calci.dir/clean

mylib/CMakeFiles/calci.dir/depend:
	cd /home/aman2003/SEM5/SE/Assignments/CMake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aman2003/SEM5/SE/Assignments/CMake /home/aman2003/SEM5/SE/Assignments/CMake/mylib /home/aman2003/SEM5/SE/Assignments/CMake/build /home/aman2003/SEM5/SE/Assignments/CMake/build/mylib /home/aman2003/SEM5/SE/Assignments/CMake/build/mylib/CMakeFiles/calci.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : mylib/CMakeFiles/calci.dir/depend
