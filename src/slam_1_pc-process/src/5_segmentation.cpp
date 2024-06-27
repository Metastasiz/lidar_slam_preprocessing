#include <iostream>
#include <filesystem>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/features/normal_3d.h>

typedef pcl::PointXYZ PointT;

int main()
{
    // ********************************		Import PCD
    pcl::PointCloud<PointT>::Ptr input_cloud (new pcl::PointCloud<PointT>);

    pcl::PCDReader cloud_reader;
    pcl::PCDWriter cloud_writer;

    std::string import_file_pcd         = "4_world_after.pcd";
    std::string export_file_pcd_before  = "5_world_before.pcd";
    std::string export_file_pcd_after   = "5_world_after.pcd";
    std::string dir_pcd                 = "slam_1_pc-process/data";
    std::filesystem::path path_ros_ws   = std::filesystem::current_path();
    std::filesystem::path path_dir_pcd  = path_ros_ws/"src"/dir_pcd;
    std::string path_import             = path_dir_pcd/import_file_pcd;
    std::string path_export_before      = path_dir_pcd/export_file_pcd_before;
    std::string path_export_after       = path_dir_pcd/export_file_pcd_after;

    cloud_reader.read(path_import,*input_cloud);

    //  ********************************    Plane Segmentation
    pcl::PointCloud<PointT>::Ptr export_cloud (new pcl::PointCloud<PointT>) ;

    pcl::PointCloud<pcl::Normal>::Ptr plane_normals(new pcl::PointCloud<pcl::Normal>);
    pcl::PointIndices::Ptr plane_inliers(new pcl::PointIndices);
    pcl::ModelCoefficients::Ptr plane_coefficients(new pcl::ModelCoefficients);

    //  Extracting Normals
    pcl::NormalEstimation<PointT, pcl::Normal> normal_extractor;
    pcl::search::KdTree<PointT>::Ptr tree(new pcl::search::KdTree<PointT>());
    normal_extractor.setSearchMethod(tree);
    normal_extractor.setKSearch(30);
    //
    normal_extractor.setInputCloud(input_cloud);
    normal_extractor.compute(*plane_normals);

    //  Parameters for Plane Segmentation
    pcl::SACSegmentationFromNormals<PointT, pcl::Normal> plane_segmentator_norms;
    plane_segmentator_norms.setOptimizeCoefficients(true);
    plane_segmentator_norms.setModelType(pcl::SACMODEL_NORMAL_PLANE);
    plane_segmentator_norms.setMethodType(pcl::SAC_RANSAC);
    plane_segmentator_norms.setNormalDistanceWeight(0.5);
    plane_segmentator_norms.setMaxIterations(100);
    plane_segmentator_norms.setDistanceThreshold(0.4);
    //
    plane_segmentator_norms.setInputCloud(input_cloud);
    plane_segmentator_norms.setInputNormals(plane_normals);
    plane_segmentator_norms.segment(*plane_inliers,*plane_coefficients);

    //  Extracting from indices
    pcl::ExtractIndices<PointT> plane_extract_indices;
    plane_extract_indices.setIndices(plane_inliers);
    plane_extract_indices.setNegative(true);
    //
    plane_extract_indices.setInputCloud(input_cloud);
    plane_extract_indices.filter(*export_cloud);

    // ********************************		Export PCD

    cloud_writer.write<PointT>(path_export_before,*input_cloud);
    cloud_writer.write<PointT>(path_export_after,*export_cloud);
    std::cout << "Saved PCD to: " << path_export_before << std::endl;
    std::cout << "Saved PCD to: " << path_export_after << std::endl;
    
  return 0;
}