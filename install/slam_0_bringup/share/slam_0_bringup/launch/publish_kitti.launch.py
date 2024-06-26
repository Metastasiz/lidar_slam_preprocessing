from launch import LaunchDescription
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node
import os

def generate_launch_description():

    return LaunchDescription([
        Node(
            package='ros2_kitti_publishers', executable='kitti_publishers', output='screen',
            ),
        Node(
            package='slam_1_pc-process', executable='main', output='screen',
            ),
    ])
