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
CMAKE_COMMAND = /home/kiwi/IDE/clion-2018.1.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/kiwi/IDE/clion-2018.1.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kiwi/Repos/Kiwi/unit_test_src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kiwi/Repos/Kiwi/unit_test_src/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Acceptor_UnitTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Acceptor_UnitTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Acceptor_UnitTest.dir/flags.make

CMakeFiles/Acceptor_UnitTest.dir/Acceptor_UnitTest.cpp.o: CMakeFiles/Acceptor_UnitTest.dir/flags.make
CMakeFiles/Acceptor_UnitTest.dir/Acceptor_UnitTest.cpp.o: ../Acceptor_UnitTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiwi/Repos/Kiwi/unit_test_src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Acceptor_UnitTest.dir/Acceptor_UnitTest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Acceptor_UnitTest.dir/Acceptor_UnitTest.cpp.o -c /home/kiwi/Repos/Kiwi/unit_test_src/Acceptor_UnitTest.cpp

CMakeFiles/Acceptor_UnitTest.dir/Acceptor_UnitTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Acceptor_UnitTest.dir/Acceptor_UnitTest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiwi/Repos/Kiwi/unit_test_src/Acceptor_UnitTest.cpp > CMakeFiles/Acceptor_UnitTest.dir/Acceptor_UnitTest.cpp.i

CMakeFiles/Acceptor_UnitTest.dir/Acceptor_UnitTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Acceptor_UnitTest.dir/Acceptor_UnitTest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiwi/Repos/Kiwi/unit_test_src/Acceptor_UnitTest.cpp -o CMakeFiles/Acceptor_UnitTest.dir/Acceptor_UnitTest.cpp.s

CMakeFiles/Acceptor_UnitTest.dir/Acceptor_UnitTest.cpp.o.requires:

.PHONY : CMakeFiles/Acceptor_UnitTest.dir/Acceptor_UnitTest.cpp.o.requires

CMakeFiles/Acceptor_UnitTest.dir/Acceptor_UnitTest.cpp.o.provides: CMakeFiles/Acceptor_UnitTest.dir/Acceptor_UnitTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/Acceptor_UnitTest.dir/build.make CMakeFiles/Acceptor_UnitTest.dir/Acceptor_UnitTest.cpp.o.provides.build
.PHONY : CMakeFiles/Acceptor_UnitTest.dir/Acceptor_UnitTest.cpp.o.provides

CMakeFiles/Acceptor_UnitTest.dir/Acceptor_UnitTest.cpp.o.provides.build: CMakeFiles/Acceptor_UnitTest.dir/Acceptor_UnitTest.cpp.o


# Object files for target Acceptor_UnitTest
Acceptor_UnitTest_OBJECTS = \
"CMakeFiles/Acceptor_UnitTest.dir/Acceptor_UnitTest.cpp.o"

# External object files for target Acceptor_UnitTest
Acceptor_UnitTest_EXTERNAL_OBJECTS =

Acceptor_UnitTest: CMakeFiles/Acceptor_UnitTest.dir/Acceptor_UnitTest.cpp.o
Acceptor_UnitTest: CMakeFiles/Acceptor_UnitTest.dir/build.make
Acceptor_UnitTest: ../../lib_release/libkiwi.a
Acceptor_UnitTest: CMakeFiles/Acceptor_UnitTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kiwi/Repos/Kiwi/unit_test_src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Acceptor_UnitTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Acceptor_UnitTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Acceptor_UnitTest.dir/build: Acceptor_UnitTest

.PHONY : CMakeFiles/Acceptor_UnitTest.dir/build

CMakeFiles/Acceptor_UnitTest.dir/requires: CMakeFiles/Acceptor_UnitTest.dir/Acceptor_UnitTest.cpp.o.requires

.PHONY : CMakeFiles/Acceptor_UnitTest.dir/requires

CMakeFiles/Acceptor_UnitTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Acceptor_UnitTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Acceptor_UnitTest.dir/clean

CMakeFiles/Acceptor_UnitTest.dir/depend:
	cd /home/kiwi/Repos/Kiwi/unit_test_src/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kiwi/Repos/Kiwi/unit_test_src /home/kiwi/Repos/Kiwi/unit_test_src /home/kiwi/Repos/Kiwi/unit_test_src/cmake-build-debug /home/kiwi/Repos/Kiwi/unit_test_src/cmake-build-debug /home/kiwi/Repos/Kiwi/unit_test_src/cmake-build-debug/CMakeFiles/Acceptor_UnitTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Acceptor_UnitTest.dir/depend

