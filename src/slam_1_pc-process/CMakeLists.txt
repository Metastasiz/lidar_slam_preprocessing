cmake_minimum_required(VERSION 3.8)
project(slam_1_pc-process)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

find_package(ament_cmake REQUIRED)
find_package(PCL REQUIRED)

find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(visualization_msgs REQUIRED)

# add executable
add_executable(1_import_pcd src/1_import_pcd.cpp)
target_link_libraries(1_import_pcd ${PCL_LIBRARIES})

add_executable(2_manual_pcd src/2_manual_pcd.cpp)
target_link_libraries(2_manual_pcd ${PCL_LIBRARIES})

add_executable(3_voxel_grid src/3_voxel_grid.cpp)
target_link_libraries(3_voxel_grid ${PCL_LIBRARIES})

add_executable(4_passthrough src/4_passthrough.cpp)
target_link_libraries(4_passthrough ${PCL_LIBRARIES})

add_executable(5_segmentation src/5_segmentation.cpp)
target_link_libraries(5_segmentation ${PCL_LIBRARIES})

add_executable(6_clustering src/6_clustering.cpp)
target_link_libraries(6_clustering ${PCL_LIBRARIES})

add_executable(main src/main.cpp)
target_link_libraries(main ${PCL_LIBRARIES})
ament_target_dependencies(main rclcpp sensor_msgs pcl_conversions visualization_msgs)


# final
install(TARGETS
  1_import_pcd 2_manual_pcd 3_voxel_grid 4_passthrough 5_segmentation 6_clustering main
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
