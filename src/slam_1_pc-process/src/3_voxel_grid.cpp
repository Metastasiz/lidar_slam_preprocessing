#include <iostream>
#include <filesystem>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

#include <pcl/filters/voxel_grid.h>

typedef pcl::PointXYZ PointT;

int main()
{
    // ********************************		Import PCD
    pcl::PointCloud<PointT>::Ptr cloud (new pcl::PointCloud<PointT>);

    pcl::PCDReader cloud_reader;
    pcl::PCDWriter cloud_writer;

    std::string import_file_pcd         = "raw_world.pcd";
    std::string export_file_pcd         = "3_world.pcd";
    std::string dir_pcd                 = "slam_1_pc-process/data";
	  std::filesystem::path path_ros_ws   = std::filesystem::current_path();
    std::filesystem::path path_dir_pcd  = path_ros_ws/"src"/dir_pcd;
    std::string path_import             = path_dir_pcd/import_file_pcd;
    std::string path_export             = path_dir_pcd/export_file_pcd;

    cloud_reader.read(path_import,*cloud);

    // ********************************   Voxel Filter
    pcl::PointCloud<PointT>::Ptr export_cloud (new pcl::PointCloud<PointT>);

    pcl::VoxelGrid<PointT> voxel_filter;
    voxel_filter.setInputCloud(cloud);
    voxel_filter.setLeafSize(0.05 , 0.05, 0.05);
    voxel_filter.filter(*export_cloud);

    // ********************************		Export PCD

    cloud_writer.write<PointT>(path_export,*export_cloud);
    std::cout << "Saved PCD to: " << path_export << std::endl;

  return 0;
}