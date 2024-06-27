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
#include <pcl/point_cloud.h>

typedef pcl::PointXYZ PointT;

void export_pcd(const std::string& file_name,std::string& path, pcl::PointCloud<PointT>::Ptr cloud_arg){
    pcl::PCDWriter cloud_writer;
    cloud_writer.write<PointT>(path+std::string(file_name),*cloud_arg);
    std::cout << "Saved PCD to: " << path+std::string(file_name) << std::endl;
}

int main()
{
    // ********************************		Import PCD
    pcl::PointCloud<PointT>::Ptr input_cloud (new pcl::PointCloud<PointT>);

    pcl::PCDReader cloud_reader;
    pcl::PCDWriter cloud_writer;

    std::string import_file_pcd         = "5_world_after.pcd";
    std::string export_file_pcd_before  = "6_world_before.pcd";
    std::string export_file_pcd_after   = "6_world_after.pcd";
    std::string dir_pcd                 = "slam_1_pc-process/data";
    std::filesystem::path path_ros_ws   = std::filesystem::current_path();
    std::filesystem::path path_dir_pcd  = path_ros_ws/"src"/dir_pcd;
    std::string path_import             = path_dir_pcd/import_file_pcd;
    std::string path_export_before      = path_dir_pcd/export_file_pcd_before;
    std::string path_export_after       = path_dir_pcd/export_file_pcd_after;

    cloud_reader.read(path_import,*input_cloud);
    //
    std::string path_dir_pcd_string     = path_dir_pcd/"";

    //  ********************************    Euclidean Clustering Indices Extraction
    pcl::PointCloud<PointT>::Ptr export_cloud (new pcl::PointCloud<PointT>);

    std::vector<pcl::PointIndices> cluster_indices;
    pcl::search::KdTree<PointT>::Ptr tree (new pcl::search::KdTree<PointT> ());

    size_t min_cluster_size = 150;
    size_t max_cluster_size = 2000;

    //  Extract indices using EC with K-D tree method
    pcl::EuclideanClusterExtraction<PointT> euclid_extract_cluster;
    euclid_extract_cluster.setClusterTolerance(0.25); // 2cm
    euclid_extract_cluster.setMinClusterSize(min_cluster_size);
    euclid_extract_cluster.setMaxClusterSize(max_cluster_size);
    euclid_extract_cluster.setSearchMethod(tree);
    //
    euclid_extract_cluster.setInputCloud(input_cloud);
    euclid_extract_cluster.extract(cluster_indices);

    //  ********************************    Filtering Cluster by Size
    int loop_counter = 1;
    for (size_t i = 0; i < cluster_indices.size(); i++)
    {
      if (cluster_indices[i].indices.size() > min_cluster_size && cluster_indices[i].indices.size() < max_cluster_size)
      {
        pcl::PointCloud<PointT>::Ptr filtered_cluster (new pcl::PointCloud<PointT>);
        pcl::IndicesPtr indices (new std::vector<int>(cluster_indices[i].indices.begin(), cluster_indices[i].indices.end()));
        
        //  Extracting from indices
        pcl::ExtractIndices<PointT> extract;
        extract.setIndices(indices);
        extract.setNegative (false);
        //
        extract.setInputCloud(input_cloud);
        extract.filter(*filtered_cluster);

        // ********************************   Export PCD (each cluster)
        std::stringstream cloud_name;
        cloud_name << "6_cluster_" << loop_counter << ".pcd";
        export_pcd(cloud_name.str(),path_dir_pcd_string,filtered_cluster);
        loop_counter++;

        // Add filtered cluster to filtered cluster group (export_cloud)
        export_cloud->operator+=(*filtered_cluster);
      }
    }

    // ********************************   Export PCD

    cloud_writer.write<PointT>(path_export_before,*input_cloud);
    cloud_writer.write<PointT>(path_export_after,*export_cloud);
    std::cout << "Saved PCD to: " << path_export_before << std::endl;
    std::cout << "Saved PCD to: " << path_export_after << std::endl;

  return 0;
}