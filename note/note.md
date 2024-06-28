# This is a note of useful commands during building the project
pcl_viewer [path_to_pcd]

https://github.com/ROBOTIS-GIT/turtlebot3_simulations/tree/master/turtlebot3_gazebo

~/.bashrc

export TURTLEBOT3_MODEL=waffle

src/turtlebot3_gazebo/models/turtlebot3_waffle/model.sdf

change sensor type="depth"

check with ros2 topic list for camera/depth/image_raw

ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py 

might be a while for Gazebo to launch first time

sudo apt install ros-$ROS_DISTRO-rtabmap-ros

https://github.com/introlab/rtabmap_ros/blob/humble-devel/rtabmap_demos/launch/turtlebot3_rgbd.launch.py

pcl_viewer -multiview 2 raw_world.pcd 3_world.pcd

pcl_viewer -multiview 2 3_world.pcd 4_world.pcd

pcl_viewer 6_cluster_*.pcd

git@github.com:umtclskn/ros2_kitti_publishers.git

ros2 launch slam_0_bringup my_rviz.launch.py 

ros2 launch slam_0_bringup publish_kitti.launch.py 