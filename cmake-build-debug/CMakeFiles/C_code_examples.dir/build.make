# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = C:\Users\eugen\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.7628.27\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\eugen\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.7628.27\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\Git\C-code-examples

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\Git\C-code-examples\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/C_code_examples.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/C_code_examples.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/C_code_examples.dir/flags.make

CMakeFiles/C_code_examples.dir/leitor_escritor.c.obj: CMakeFiles/C_code_examples.dir/flags.make
CMakeFiles/C_code_examples.dir/leitor_escritor.c.obj: ../leitor_escritor.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Git\C-code-examples\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/C_code_examples.dir/leitor_escritor.c.obj"
	C:\PROGRA~2\Dev-Cpp\MinGW64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\C_code_examples.dir\leitor_escritor.c.obj -c E:\Git\C-code-examples\leitor_escritor.c

CMakeFiles/C_code_examples.dir/leitor_escritor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/C_code_examples.dir/leitor_escritor.c.i"
	C:\PROGRA~2\Dev-Cpp\MinGW64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E E:\Git\C-code-examples\leitor_escritor.c > CMakeFiles\C_code_examples.dir\leitor_escritor.c.i

CMakeFiles/C_code_examples.dir/leitor_escritor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/C_code_examples.dir/leitor_escritor.c.s"
	C:\PROGRA~2\Dev-Cpp\MinGW64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S E:\Git\C-code-examples\leitor_escritor.c -o CMakeFiles\C_code_examples.dir\leitor_escritor.c.s

# Object files for target C_code_examples
C_code_examples_OBJECTS = \
"CMakeFiles/C_code_examples.dir/leitor_escritor.c.obj"

# External object files for target C_code_examples
C_code_examples_EXTERNAL_OBJECTS =

C_code_examples.exe: CMakeFiles/C_code_examples.dir/leitor_escritor.c.obj
C_code_examples.exe: CMakeFiles/C_code_examples.dir/build.make
C_code_examples.exe: CMakeFiles/C_code_examples.dir/linklibs.rsp
C_code_examples.exe: CMakeFiles/C_code_examples.dir/objects1.rsp
C_code_examples.exe: CMakeFiles/C_code_examples.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\Git\C-code-examples\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable C_code_examples.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\C_code_examples.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/C_code_examples.dir/build: C_code_examples.exe

.PHONY : CMakeFiles/C_code_examples.dir/build

CMakeFiles/C_code_examples.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\C_code_examples.dir\cmake_clean.cmake
.PHONY : CMakeFiles/C_code_examples.dir/clean

CMakeFiles/C_code_examples.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Git\C-code-examples E:\Git\C-code-examples E:\Git\C-code-examples\cmake-build-debug E:\Git\C-code-examples\cmake-build-debug E:\Git\C-code-examples\cmake-build-debug\CMakeFiles\C_code_examples.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/C_code_examples.dir/depend
