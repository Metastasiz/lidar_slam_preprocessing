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
CMAKE_SOURCE_DIR = /home/mark/thesis/src/slam_1_pc-process

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mark/thesis/build/slam_1_pc-process

# Include any dependencies generated for this target.
include CMakeFiles/1_import_pcd.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/1_import_pcd.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/1_import_pcd.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/1_import_pcd.dir/flags.make

CMakeFiles/1_import_pcd.dir/src/1_import_pcd.cpp.o: CMakeFiles/1_import_pcd.dir/flags.make
CMakeFiles/1_import_pcd.dir/src/1_import_pcd.cpp.o: /home/mark/thesis/src/slam_1_pc-process/src/1_import_pcd.cpp
CMakeFiles/1_import_pcd.dir/src/1_import_pcd.cpp.o: CMakeFiles/1_import_pcd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/thesis/build/slam_1_pc-process/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/1_import_pcd.dir/src/1_import_pcd.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/1_import_pcd.dir/src/1_import_pcd.cpp.o -MF CMakeFiles/1_import_pcd.dir/src/1_import_pcd.cpp.o.d -o CMakeFiles/1_import_pcd.dir/src/1_import_pcd.cpp.o -c /home/mark/thesis/src/slam_1_pc-process/src/1_import_pcd.cpp

CMakeFiles/1_import_pcd.dir/src/1_import_pcd.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/1_import_pcd.dir/src/1_import_pcd.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mark/thesis/src/slam_1_pc-process/src/1_import_pcd.cpp > CMakeFiles/1_import_pcd.dir/src/1_import_pcd.cpp.i

CMakeFiles/1_import_pcd.dir/src/1_import_pcd.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/1_import_pcd.dir/src/1_import_pcd.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mark/thesis/src/slam_1_pc-process/src/1_import_pcd.cpp -o CMakeFiles/1_import_pcd.dir/src/1_import_pcd.cpp.s

# Object files for target 1_import_pcd
1_import_pcd_OBJECTS = \
"CMakeFiles/1_import_pcd.dir/src/1_import_pcd.cpp.o"

# External object files for target 1_import_pcd
1_import_pcd_EXTERNAL_OBJECTS =

1_import_pcd: CMakeFiles/1_import_pcd.dir/src/1_import_pcd.cpp.o
1_import_pcd: CMakeFiles/1_import_pcd.dir/build.make
1_import_pcd: /usr/lib/x86_64-linux-gnu/libpcl_apps.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libpcl_outofcore.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libpcl_people.so
1_import_pcd: /usr/lib/libOpenNI.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libOpenNI2.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libflann_cpp.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libpcl_surface.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libpcl_keypoints.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libpcl_tracking.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libpcl_recognition.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libpcl_registration.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libpcl_stereo.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libpcl_segmentation.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libpcl_features.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libpcl_filters.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libpcl_sample_consensus.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libpcl_ml.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libpcl_visualization.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libpcl_search.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libpcl_kdtree.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libpcl_io.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libpcl_octree.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libpng.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libz.so
1_import_pcd: /usr/lib/libOpenNI.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libOpenNI2.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkChartsCore-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkInteractionImage-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkIOGeometry-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libjsoncpp.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkIOPLY-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkRenderingLOD-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkViewsContext2D-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkViewsCore-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkGUISupportQt-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkInteractionWidgets-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkFiltersModeling-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkInteractionStyle-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkFiltersExtraction-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkIOLegacy-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkIOCore-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkRenderingAnnotation-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkRenderingContext2D-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkRenderingFreeType-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libfreetype.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkImagingSources-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkIOImage-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkImagingCore-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkRenderingOpenGL2-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkRenderingUI-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkRenderingCore-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkCommonColor-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkFiltersGeometry-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkFiltersSources-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkFiltersGeneral-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkCommonComputationalGeometry-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkFiltersCore-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkCommonExecutionModel-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkCommonDataModel-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkCommonMisc-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkCommonTransforms-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkCommonMath-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkkissfft-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libGLEW.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libX11.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libQt5OpenGL.so.5.15.3
1_import_pcd: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
1_import_pcd: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3
1_import_pcd: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtkCommonCore-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libtbb.so.12.5
1_import_pcd: /usr/lib/x86_64-linux-gnu/libvtksys-9.1.so.9.1.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libpcl_common.so
1_import_pcd: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.74.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.74.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libboost_date_time.so.1.74.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libboost_iostreams.so.1.74.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libboost_serialization.so.1.74.0
1_import_pcd: /usr/lib/x86_64-linux-gnu/libqhull_r.so.8.0.2
1_import_pcd: CMakeFiles/1_import_pcd.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mark/thesis/build/slam_1_pc-process/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 1_import_pcd"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/1_import_pcd.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/1_import_pcd.dir/build: 1_import_pcd
.PHONY : CMakeFiles/1_import_pcd.dir/build

CMakeFiles/1_import_pcd.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/1_import_pcd.dir/cmake_clean.cmake
.PHONY : CMakeFiles/1_import_pcd.dir/clean

CMakeFiles/1_import_pcd.dir/depend:
	cd /home/mark/thesis/build/slam_1_pc-process && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mark/thesis/src/slam_1_pc-process /home/mark/thesis/src/slam_1_pc-process /home/mark/thesis/build/slam_1_pc-process /home/mark/thesis/build/slam_1_pc-process /home/mark/thesis/build/slam_1_pc-process/CMakeFiles/1_import_pcd.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/1_import_pcd.dir/depend

