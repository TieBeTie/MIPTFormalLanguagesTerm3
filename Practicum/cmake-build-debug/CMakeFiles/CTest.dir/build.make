# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /snap/clion/129/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/129/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tiebetie/CLionProjects/Practicum

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tiebetie/CLionProjects/Practicum/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CTest.dir/flags.make

CMakeFiles/CTest.dir/main_test.cpp.o: CMakeFiles/CTest.dir/flags.make
CMakeFiles/CTest.dir/main_test.cpp.o: ../main_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tiebetie/CLionProjects/Practicum/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CTest.dir/main_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CTest.dir/main_test.cpp.o -c /home/tiebetie/CLionProjects/Practicum/main_test.cpp

CMakeFiles/CTest.dir/main_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CTest.dir/main_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tiebetie/CLionProjects/Practicum/main_test.cpp > CMakeFiles/CTest.dir/main_test.cpp.i

CMakeFiles/CTest.dir/main_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CTest.dir/main_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tiebetie/CLionProjects/Practicum/main_test.cpp -o CMakeFiles/CTest.dir/main_test.cpp.s

# Object files for target CTest
CTest_OBJECTS = \
"CMakeFiles/CTest.dir/main_test.cpp.o"

# External object files for target CTest
CTest_EXTERNAL_OBJECTS =

CTest: CMakeFiles/CTest.dir/main_test.cpp.o
CTest: CMakeFiles/CTest.dir/build.make
CTest: lib/libgtestd.a
CTest: CMakeFiles/CTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tiebetie/CLionProjects/Practicum/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable CTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CTest.dir/build: CTest

.PHONY : CMakeFiles/CTest.dir/build

CMakeFiles/CTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CTest.dir/clean

CMakeFiles/CTest.dir/depend:
	cd /home/tiebetie/CLionProjects/Practicum/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tiebetie/CLionProjects/Practicum /home/tiebetie/CLionProjects/Practicum /home/tiebetie/CLionProjects/Practicum/cmake-build-debug /home/tiebetie/CLionProjects/Practicum/cmake-build-debug /home/tiebetie/CLionProjects/Practicum/cmake-build-debug/CMakeFiles/CTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CTest.dir/depend

