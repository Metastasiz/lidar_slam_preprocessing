#include <iostream>
#include <filesystem>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/filters/extract_indices.h>

#include <pcl/search/search.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d.h>

typedef pcl::PointXYZ PointT;

void export_pcd(const std::string& file_name,std::string& path, pcl::PointCloud<PointT>::Ptr cloud_arg){
    pcl::PCDWriter cloud_writer;
    cloud_writer.write<PointT>(path+std::string(file_name),*cloud_arg);
    std::cout << "Saved PCD to: " << path+std::string(file_name) << std::endl;
}

int main()
{
    // ********************************		Import PCD
    pcl::PointCloud<PointT>::Ptr cloud (new pcl::PointCloud<PointT>);

    pcl::PCDReader cloud_reader;
    pcl::PCDWriter cloud_writer;

    std::string import_file_pcd         = "5_world.pcd";
    std::string export_file_pcd         = "6_world.pcd";
    std::string dir_pcd                 = "slam_1_pc-process/data";
	std::filesystem::path path_ros_ws   = std::filesystem::current_path();
    std::filesystem::path path_dir_pcd  = path_ros_ws/"src"/dir_pcd;
    std::string path_dir_pcd_string     = path_dir_pcd/"";
    std::string path_import             = path_dir_pcd/import_file_pcd;
    std::string path_export             = path_dir_pcd/export_file_pcd;

    cloud_reader.read(path_import,*cloud);

    // ********************************     Cylinder Clustering
    pcl::PointCloud<PointT>::Ptr cylinder_cloud (new pcl::PointCloud<PointT>);

    pcl::PointIndices::Ptr inliers (new pcl::PointIndices);
    pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);
    pcl::PointCloud<pcl::Normal>::Ptr cloud_normals (new pcl::PointCloud<pcl::Normal>);
    
    // Estimation of normals
    pcl::NormalEstimation<PointT,pcl::Normal> normals_estimator;
    pcl::search::KdTree<PointT>::Ptr tree (new pcl::search::KdTree<PointT> ());
    normals_estimator.setSearchMethod(tree);
    normals_estimator.setInputCloud(cloud);
    normals_estimator.setKSearch(30);
    normals_estimator.compute(*cloud_normals);

    // Parameters for segmentation
    pcl::SACSegmentationFromNormals<PointT, pcl::Normal> cylinder_segmentor;
	cylinder_segmentor.setModelType(pcl::SACMODEL_CYLINDER);
	cylinder_segmentor.setMethodType(pcl::SAC_RANSAC);
	cylinder_segmentor.setDistanceThreshold(0.05);
    //
    cylinder_segmentor.setOptimizeCoefficients(true);
	cylinder_segmentor.setNormalDistanceWeight(0.5);
	cylinder_segmentor.setMaxIterations(10000);
	cylinder_segmentor.setRadiusLimits(0.1,0.4);

    int loop_counter = 1;
    pcl::ExtractIndices<PointT> cylinder_indices_extractor;
    pcl::ExtractIndices<pcl::Normal> cylinder_normal_indices_extractor;
    while(true)
    {
        // Appplying segmentation
        cylinder_segmentor.setInputCloud(cloud);
        cylinder_segmentor.setInputNormals(cloud_normals);
        cylinder_segmentor.segment(*inliers,*coefficients);

        // Extracting indices
        cylinder_indices_extractor.setInputCloud(cloud);
        cylinder_indices_extractor.setIndices(inliers);
        cylinder_indices_extractor.setNegative(false);
        cylinder_indices_extractor.filter(*cylinder_cloud);
        if(!cylinder_cloud->points.empty())
        {
            std::stringstream cloud_name;
            if(cylinder_cloud->points.size()>50){
                cloud_name << "6_cluster_" << loop_counter << ".pcd";
                export_pcd(cloud_name.str(),path_dir_pcd_string,cylinder_cloud);
                loop_counter++;
            }
            // Mark this indices as imported
            cylinder_indices_extractor.setNegative(true);
            cylinder_indices_extractor.filter(*cloud);

            // Extracting normals
            cylinder_normal_indices_extractor.setInputCloud(cloud_normals);
            cylinder_normal_indices_extractor.setIndices(inliers);
            cylinder_normal_indices_extractor.setNegative(true);
            cylinder_normal_indices_extractor.filter(*cloud_normals);
        }
        else {return 0;}
    }

  return 0;
}