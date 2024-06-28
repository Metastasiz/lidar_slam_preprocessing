# Lidar SLAM Preprocessing
This is a ROS2 node for preprocessing Lidar data\
Thanondrak, Mark\
24th June 2024
# How to launch
## Downloading Dataset
in ros2 workspace\
	`data/raw_data_downloader.sh`
## For bringing up rviz and preferred saved config 
ros2 launch slam_0_bringup my_rviz.launch.py 
## For publishing processed data from kitti dataset
ros2 launch slam_0_bringup publish_kitti.launch.py 
# Subscription
## Kitti Lidar Dataset
ROS2 node subscription: kitti/point_cloud
# Publishing
## Object Clusters
ROS2 node publishes: cluster_cloud
## Object Bounding Box
ROS2 node publishes: visualization_marker_array