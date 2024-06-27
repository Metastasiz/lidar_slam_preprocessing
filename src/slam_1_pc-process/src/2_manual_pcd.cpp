#include <iostream>
#include <filesystem>

#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>

typedef pcl::PointXYZ PointT;

int main()
{
    // ********************************		Import PCD
    pcl::PointCloud<PointT> export_cloud;

    pcl::PCDWriter cloud_writer;

    std::string export_file_pcd_after   = "2_world.pcd";
    std::string dir_pcd                 = "slam_1_pc-process/data";
    std::filesystem::path path_ros_ws   = std::filesystem::current_path();
    std::filesystem::path path_dir_pcd  = path_ros_ws/"src"/dir_pcd;
    std::string path_export_after       = path_dir_pcd/export_file_pcd_after;

    // ********************************		Manually Adding Point Cloud Data
    export_cloud.push_back(PointT(1.0 ,2.0 ,3.0));
    export_cloud.push_back(PointT(4.0 ,5.0 ,3.0));
    export_cloud.push_back(PointT(7.0 ,8.0 ,3.0));
    export_cloud.push_back(PointT(10.0,11.0,3.0));
    export_cloud.push_back(PointT(12.0,14.0,3.0));

    cloud_writer.write<PointT>(path_export_after,export_cloud);

    std::cout << "Manually created: " << path_export_after << std::endl;
    std::cout << "Number of points: " << export_cloud.size() << std::endl;

    return 0;

}