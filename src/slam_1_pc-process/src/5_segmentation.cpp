#include <iostream>
#include <filesystem>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/filters/extract_indices.h>

typedef pcl::PointXYZ PointT;

int main()
{
    // ********************************		Import PCD
    pcl::PointCloud<PointT>::Ptr cloud (new pcl::PointCloud<PointT>);

    pcl::PCDReader cloud_reader;
    pcl::PCDWriter cloud_writer;

    std::string import_file_pcd         = "4_world.pcd";
    std::string export_file_pcd         = "5_world.pcd";
    std::string dir_pcd                 = "slam_1_pc-process/data";
	std::filesystem::path path_ros_ws   = std::filesystem::current_path();
    std::filesystem::path path_dir_pcd  = path_ros_ws/"src"/dir_pcd;
    std::string path_import             = path_dir_pcd/import_file_pcd;
    std::string path_export             = path_dir_pcd/export_file_pcd;

    cloud_reader.read(path_import,*cloud);

	// ********************************     Plane Segmentation
    pcl::PointCloud<PointT>::Ptr export_cloud (new pcl::PointCloud<PointT>);

    pcl::PointIndices::Ptr  inliers (new pcl::PointIndices);
    pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);

    pcl::SACSegmentation<PointT> plane_segmentor;
    plane_segmentor.setInputCloud(cloud);
    plane_segmentor.setModelType(pcl::SACMODEL_PLANE);
    plane_segmentor.setMethodType(pcl::SAC_RANSAC);
    plane_segmentor.setDistanceThreshold(0.01);
	// segmentor produces inliers and coefficients
    plane_segmentor.segment(*inliers,*coefficients);

    pcl::ExtractIndices<PointT> plane_indices_extractor;
    plane_indices_extractor.setInputCloud(cloud);
    plane_indices_extractor.setIndices(inliers);
    plane_indices_extractor.setNegative(true);
    plane_indices_extractor.filter(*export_cloud);

    // ********************************		Export PCD

    cloud_writer.write<PointT>(path_export,*export_cloud);
    std::cout << "Saved PCD to: " << path_export << std::endl;

  return 0;
}