#include <iostream>
#include <filesystem>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

#include <pcl/filters/passthrough.h>

typedef pcl::PointXYZ PointT;

int main()
{
    // ********************************		Import PCD
    pcl::PointCloud<PointT>::Ptr input_cloud (new pcl::PointCloud<PointT>);

    pcl::PCDReader cloud_reader;
    pcl::PCDWriter cloud_writer;

    std::string import_file_pcd         = "3_world_after.pcd";
    std::string export_file_pcd_before  = "4_world_before.pcd";
    std::string export_file_pcd_after   = "4_world_after.pcd";
    std::string dir_pcd                 = "slam_1_pc-process/data";
    std::filesystem::path path_ros_ws   = std::filesystem::current_path();
    std::filesystem::path path_dir_pcd  = path_ros_ws/"src"/dir_pcd;
    std::string path_import             = path_dir_pcd/import_file_pcd;
    std::string path_export_before      = path_dir_pcd/export_file_pcd_before;
    std::string path_export_after       = path_dir_pcd/export_file_pcd_after;

    cloud_reader.read(path_import,*input_cloud);

    // ********************************   Voxel Filter
    pcl::PointCloud<PointT>::Ptr export_cloud (new pcl::PointCloud<PointT>) ;

    // Along X Axis
    pcl::PassThrough<PointT> passing_x;
    passing_x.setFilterFieldName("x");
    passing_x.setFilterLimits(-1.7,1.7);
    //
    passing_x.setInputCloud(input_cloud);
    passing_x.filter(*export_cloud);

    // Along Y Axis
    pcl::PassThrough<PointT> passing_y;
    passing_y.setFilterFieldName("y");
    passing_y.setFilterLimits(-1.7,1.7);
    //
    passing_y.setInputCloud(export_cloud);
    passing_y.filter(*export_cloud);

    // ********************************		Export PCD

    cloud_writer.write<PointT>(path_export_before,*input_cloud);
    cloud_writer.write<PointT>(path_export_after,*export_cloud);
    std::cout << "Saved PCD to: " << path_export_before << std::endl;
    std::cout << "Saved PCD to: " << path_export_after << std::endl;

  return 0;
}