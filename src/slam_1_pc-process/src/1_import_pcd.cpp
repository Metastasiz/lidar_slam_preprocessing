#include <iostream>
#include <filesystem>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>

int main()
{
    pcl::PCLPointCloud2::Ptr cloud (new pcl::PCLPointCloud2());

    pcl::PCDReader cloud_reader;

    std::string import_file_pcd         = "tb3_world.pcd";
    std::string dir_pcd                 = "slam_1_pc-process/data";
    std::filesystem::path path_ros_ws   = std::filesystem::current_path();
    std::filesystem::path path_dir_pcd  = path_ros_ws/"src"/dir_pcd;
    std::string path_import             = path_dir_pcd/import_file_pcd;

    cloud_reader.read(path_import,*cloud);
    
    std::cout << "Number of points: " << cloud->width * cloud->height << std::endl;

    return 0;
}