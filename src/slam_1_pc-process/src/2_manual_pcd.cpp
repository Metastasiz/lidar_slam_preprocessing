#include <iostream>
#include <filesystem>

#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>

int main()
{
    pcl::PointCloud<pcl::PointXYZ> cloud ;

    pcl::PCDWriter cloud_writer;

    std::string export_file_pcd         = "manual_pcd.pcd";
    std::string dir_pcd                 = "slam_1_pc-process/data";
	std::filesystem::path path_ros_ws   = std::filesystem::current_path();
    std::filesystem::path path_dir_pcd  = path_ros_ws/"src"/dir_pcd;
    std::string path_export             = path_dir_pcd/export_file_pcd;

    cloud.push_back(pcl::PointXYZ(1.0 ,2.0 ,3.0));
    cloud.push_back(pcl::PointXYZ(4.0 ,5.0 ,3.0));
    cloud.push_back(pcl::PointXYZ(7.0 ,8.0 ,3.0));
    cloud.push_back(pcl::PointXYZ(10.0,11.0,3.0));
    cloud.push_back(pcl::PointXYZ(12.0,14.0,3.0));

    cloud_writer.write<pcl::PointXYZ>(path_export,cloud);

    std::cout << "Manually created: " << path_export << std::endl;
    std::cout << "Number of points: " << cloud.size() << std::endl;

    return 0;

}