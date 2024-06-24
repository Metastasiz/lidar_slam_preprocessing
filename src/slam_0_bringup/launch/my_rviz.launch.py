from launch import LaunchDescription
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node
import os

def generate_launch_description():
    path_config = os.path.join(get_package_share_directory('slam_0_bringup'),'rviz','rviz_kitti.rviz')

    return LaunchDescription([
        Node(
            package='rviz2', executable='rviz2', output='screen',
            arguments=['-d', path_config]
            ),
    ])