# Lidar SLAM Preprocessing
This is a ROS2 node for preprocessing Lidar data\
(will update a bit later)\
Thanondrak, Mark\
24th June 2024
# Algorithms
## Voxel Grid Filter
## Passthrough Filter
## Plane Segmentation
## Object Clustering
# Subscription
## Kitti Lidar Dataset
ROS2 node subscription: kitti/point_cloud
# Publishing
## Object Clusters
ROS2 node publishes: cluster_cloud
## Object Bounding Box
ROS2 node publishes: visualization_marker_array
# How to launch
## For bringing up rviz and preferred saved config 
ros2 launch slam_0_bringup my_rviz.launch.py 
## For publishing processed data from kitti dataset
ros2 launch slam_0_bringup publish_kitti.launch.py 
