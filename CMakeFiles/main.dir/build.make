# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_SOURCE_DIR = /home/sas/Coding/sdmProj

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sas/Coding/sdmProj

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.cpp.o: main.cpp
CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sas/Coding/sdmProj/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/main.cpp.o -MF CMakeFiles/main.dir/main.cpp.o.d -o CMakeFiles/main.dir/main.cpp.o -c /home/sas/Coding/sdmProj/main.cpp

CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sas/Coding/sdmProj/main.cpp > CMakeFiles/main.dir/main.cpp.i

CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sas/Coding/sdmProj/main.cpp -o CMakeFiles/main.dir/main.cpp.s

CMakeFiles/main.dir/source/DataBase.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/source/DataBase.cpp.o: source/DataBase.cpp
CMakeFiles/main.dir/source/DataBase.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sas/Coding/sdmProj/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/source/DataBase.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/source/DataBase.cpp.o -MF CMakeFiles/main.dir/source/DataBase.cpp.o.d -o CMakeFiles/main.dir/source/DataBase.cpp.o -c /home/sas/Coding/sdmProj/source/DataBase.cpp

CMakeFiles/main.dir/source/DataBase.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/source/DataBase.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sas/Coding/sdmProj/source/DataBase.cpp > CMakeFiles/main.dir/source/DataBase.cpp.i

CMakeFiles/main.dir/source/DataBase.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/source/DataBase.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sas/Coding/sdmProj/source/DataBase.cpp -o CMakeFiles/main.dir/source/DataBase.cpp.s

CMakeFiles/main.dir/source/Doctor.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/source/Doctor.cpp.o: source/Doctor.cpp
CMakeFiles/main.dir/source/Doctor.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sas/Coding/sdmProj/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/source/Doctor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/source/Doctor.cpp.o -MF CMakeFiles/main.dir/source/Doctor.cpp.o.d -o CMakeFiles/main.dir/source/Doctor.cpp.o -c /home/sas/Coding/sdmProj/source/Doctor.cpp

CMakeFiles/main.dir/source/Doctor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/source/Doctor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sas/Coding/sdmProj/source/Doctor.cpp > CMakeFiles/main.dir/source/Doctor.cpp.i

CMakeFiles/main.dir/source/Doctor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/source/Doctor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sas/Coding/sdmProj/source/Doctor.cpp -o CMakeFiles/main.dir/source/Doctor.cpp.s

CMakeFiles/main.dir/source/HealthIssue.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/source/HealthIssue.cpp.o: source/HealthIssue.cpp
CMakeFiles/main.dir/source/HealthIssue.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sas/Coding/sdmProj/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/source/HealthIssue.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/source/HealthIssue.cpp.o -MF CMakeFiles/main.dir/source/HealthIssue.cpp.o.d -o CMakeFiles/main.dir/source/HealthIssue.cpp.o -c /home/sas/Coding/sdmProj/source/HealthIssue.cpp

CMakeFiles/main.dir/source/HealthIssue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/source/HealthIssue.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sas/Coding/sdmProj/source/HealthIssue.cpp > CMakeFiles/main.dir/source/HealthIssue.cpp.i

CMakeFiles/main.dir/source/HealthIssue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/source/HealthIssue.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sas/Coding/sdmProj/source/HealthIssue.cpp -o CMakeFiles/main.dir/source/HealthIssue.cpp.s

CMakeFiles/main.dir/source/HealthServicies.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/source/HealthServicies.cpp.o: source/HealthServicies.cpp
CMakeFiles/main.dir/source/HealthServicies.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sas/Coding/sdmProj/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main.dir/source/HealthServicies.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/source/HealthServicies.cpp.o -MF CMakeFiles/main.dir/source/HealthServicies.cpp.o.d -o CMakeFiles/main.dir/source/HealthServicies.cpp.o -c /home/sas/Coding/sdmProj/source/HealthServicies.cpp

CMakeFiles/main.dir/source/HealthServicies.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/source/HealthServicies.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sas/Coding/sdmProj/source/HealthServicies.cpp > CMakeFiles/main.dir/source/HealthServicies.cpp.i

CMakeFiles/main.dir/source/HealthServicies.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/source/HealthServicies.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sas/Coding/sdmProj/source/HealthServicies.cpp -o CMakeFiles/main.dir/source/HealthServicies.cpp.s

CMakeFiles/main.dir/source/MainSystem.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/source/MainSystem.cpp.o: source/MainSystem.cpp
CMakeFiles/main.dir/source/MainSystem.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sas/Coding/sdmProj/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/main.dir/source/MainSystem.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/source/MainSystem.cpp.o -MF CMakeFiles/main.dir/source/MainSystem.cpp.o.d -o CMakeFiles/main.dir/source/MainSystem.cpp.o -c /home/sas/Coding/sdmProj/source/MainSystem.cpp

CMakeFiles/main.dir/source/MainSystem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/source/MainSystem.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sas/Coding/sdmProj/source/MainSystem.cpp > CMakeFiles/main.dir/source/MainSystem.cpp.i

CMakeFiles/main.dir/source/MainSystem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/source/MainSystem.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sas/Coding/sdmProj/source/MainSystem.cpp -o CMakeFiles/main.dir/source/MainSystem.cpp.s

CMakeFiles/main.dir/source/MedicalEncounter.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/source/MedicalEncounter.cpp.o: source/MedicalEncounter.cpp
CMakeFiles/main.dir/source/MedicalEncounter.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sas/Coding/sdmProj/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/main.dir/source/MedicalEncounter.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/source/MedicalEncounter.cpp.o -MF CMakeFiles/main.dir/source/MedicalEncounter.cpp.o.d -o CMakeFiles/main.dir/source/MedicalEncounter.cpp.o -c /home/sas/Coding/sdmProj/source/MedicalEncounter.cpp

CMakeFiles/main.dir/source/MedicalEncounter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/source/MedicalEncounter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sas/Coding/sdmProj/source/MedicalEncounter.cpp > CMakeFiles/main.dir/source/MedicalEncounter.cpp.i

CMakeFiles/main.dir/source/MedicalEncounter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/source/MedicalEncounter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sas/Coding/sdmProj/source/MedicalEncounter.cpp -o CMakeFiles/main.dir/source/MedicalEncounter.cpp.s

CMakeFiles/main.dir/source/Patient.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/source/Patient.cpp.o: source/Patient.cpp
CMakeFiles/main.dir/source/Patient.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sas/Coding/sdmProj/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/main.dir/source/Patient.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/source/Patient.cpp.o -MF CMakeFiles/main.dir/source/Patient.cpp.o.d -o CMakeFiles/main.dir/source/Patient.cpp.o -c /home/sas/Coding/sdmProj/source/Patient.cpp

CMakeFiles/main.dir/source/Patient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/source/Patient.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sas/Coding/sdmProj/source/Patient.cpp > CMakeFiles/main.dir/source/Patient.cpp.i

CMakeFiles/main.dir/source/Patient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/source/Patient.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sas/Coding/sdmProj/source/Patient.cpp -o CMakeFiles/main.dir/source/Patient.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.o" \
"CMakeFiles/main.dir/source/DataBase.cpp.o" \
"CMakeFiles/main.dir/source/Doctor.cpp.o" \
"CMakeFiles/main.dir/source/HealthIssue.cpp.o" \
"CMakeFiles/main.dir/source/HealthServicies.cpp.o" \
"CMakeFiles/main.dir/source/MainSystem.cpp.o" \
"CMakeFiles/main.dir/source/MedicalEncounter.cpp.o" \
"CMakeFiles/main.dir/source/Patient.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

build/main: CMakeFiles/main.dir/main.cpp.o
build/main: CMakeFiles/main.dir/source/DataBase.cpp.o
build/main: CMakeFiles/main.dir/source/Doctor.cpp.o
build/main: CMakeFiles/main.dir/source/HealthIssue.cpp.o
build/main: CMakeFiles/main.dir/source/HealthServicies.cpp.o
build/main: CMakeFiles/main.dir/source/MainSystem.cpp.o
build/main: CMakeFiles/main.dir/source/MedicalEncounter.cpp.o
build/main: CMakeFiles/main.dir/source/Patient.cpp.o
build/main: CMakeFiles/main.dir/build.make
build/main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/sas/Coding/sdmProj/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable build/main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: build/main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/sas/Coding/sdmProj && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sas/Coding/sdmProj /home/sas/Coding/sdmProj /home/sas/Coding/sdmProj /home/sas/Coding/sdmProj /home/sas/Coding/sdmProj/CMakeFiles/main.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/main.dir/depend

