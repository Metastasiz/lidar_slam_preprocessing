#include <iostream>
#include <filesystem>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>

typedef pcl::PointXYZ PointT;

int main()
{
    // ********************************		Import PCD
    pcl::PointCloud<PointT>::Ptr input_cloud (new pcl::PointCloud<PointT>);

    pcl::PCDReader cloud_reader;

    std::string import_file_pcd         = "raw_world.pcd";
    std::string dir_pcd                 = "slam_1_pc-process/data";
    std::filesystem::path path_ros_ws   = std::filesystem::current_path();
    std::filesystem::path path_dir_pcd  = path_ros_ws/"src"/dir_pcd;
    std::string path_import             = path_dir_pcd/import_file_pcd;

    cloud_reader.read(path_import,*input_cloud);
    
    std::cout << "Number of points: " << input_cloud->width * input_cloud->height << std::endl;

    return 0;
}