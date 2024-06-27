#include <chrono>
#include <memory>
#include <string>

#include "std_msgs/msg/string.hpp"
#include "visualization_msgs/msg/marker_array.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "pcl_conversions/pcl_conversions.h"
#include "pcl/filters/voxel_grid.h"
#include <pcl/filters/extract_indices.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/features/normal_3d.h>
#include <pcl/segmentation/sac_segmentation.h>
#include "visualization_msgs/msg/marker_array.hpp"
#include <pcl/filters/passthrough.h>
#include <pcl/octree/octree_pointcloud.h>
#include <pcl/octree/octree.h>

#include <pcl/point_cloud.h>
using namespace std::chrono_literals;
typedef pcl::PointXYZ PointT;

class VoxelGrid_filter : public rclcpp::Node
{
  public:
    VoxelGrid_filter()
    : Node("minimal_publisher")
    {
      subscription_ =
      this->create_subscription<sensor_msgs::msg::PointCloud2>(
        "/kitti/point_cloud", 10, std::bind(&VoxelGrid_filter::timer_callback, this, std::placeholders::_1));

      publisher_ =
      this->create_publisher<sensor_msgs::msg::PointCloud2>(
        "cluster_cloud", 10);
      
      publisher_marker = 
      this->create_publisher<visualization_msgs::msg::MarkerArray>(
        "visualization_marker_array", 10);
    }

  private:
    void timer_callback(const sensor_msgs::msg::PointCloud2::SharedPtr input_cloud)
    {
      pcl::PointCloud<PointT>::Ptr pcl_cloud (new pcl::PointCloud<PointT>);
      pcl::fromROSMsg(*input_cloud, *pcl_cloud);

      //  ********************************    Passthrough
      pcl::PointCloud<PointT>::Ptr passthru_cloud (new pcl::PointCloud<PointT>) ;
      //
      int radius = 15;
      pcl::PassThrough<PointT> passing_x;
      //  Along X Axis
      passing_x.setInputCloud(pcl_cloud);
      passing_x.setFilterFieldName("x");
      passing_x.setFilterLimits(-radius,radius);
      passing_x.filter(*passthru_cloud);

      //  Along Y Axis
      pcl::PassThrough<PointT> passing_y;
      passing_y.setInputCloud(passthru_cloud);
      passing_y.setFilterFieldName("y");
      passing_y.setFilterLimits(-radius,radius);
      passing_y.filter(*passthru_cloud);

      //  ********************************    Voxel Filter
      pcl::PointCloud<PointT>::Ptr voxel_cloud (new pcl::PointCloud<PointT>) ;
      //
      pcl::VoxelGrid<PointT> voxel_filter;
      voxel_filter.setInputCloud(passthru_cloud);
      voxel_filter.setLeafSize(0.1 , 0.1, 0.1);
      voxel_filter.filter(*voxel_cloud);

      //  ********************************    Plane Segmentation
      pcl::PointCloud<PointT>::Ptr plane_cloud(new pcl::PointCloud<PointT>);
      //
      pcl::PointCloud<pcl::Normal>::Ptr plane_normals(new pcl::PointCloud<pcl::Normal>);
      pcl::PointIndices::Ptr plane_inliers(new pcl::PointIndices);
      pcl::ModelCoefficients::Ptr plane_coefficients(new pcl::ModelCoefficients);

      //  Extracting Normals
      pcl::NormalEstimation<PointT, pcl::Normal> normal_extractor;
      pcl::search::KdTree<PointT>::Ptr tree(new pcl::search::KdTree<PointT>());
      normal_extractor.setSearchMethod(tree);
      normal_extractor.setInputCloud(voxel_cloud);
      normal_extractor.setKSearch(30);
      normal_extractor.compute(*plane_normals);

      //  Parameters for Plane Segmentation
      pcl::SACSegmentationFromNormals<PointT, pcl::Normal> plane_segmentator_norms;
      plane_segmentator_norms.setOptimizeCoefficients(true);
      plane_segmentator_norms.setModelType(pcl::SACMODEL_NORMAL_PLANE);
      plane_segmentator_norms.setMethodType(pcl::SAC_RANSAC);
      plane_segmentator_norms.setNormalDistanceWeight(0.5);
      plane_segmentator_norms.setMaxIterations(100);
      plane_segmentator_norms.setDistanceThreshold(0.4);
      plane_segmentator_norms.setInputCloud(voxel_cloud);
      plane_segmentator_norms.setInputNormals(plane_normals);
      plane_segmentator_norms.segment(*plane_inliers,*plane_coefficients);

      //  Extracting from indices
      pcl::ExtractIndices<PointT> plane_extract_indices;
      plane_extract_indices.setInputCloud(voxel_cloud);
      plane_extract_indices.setIndices(plane_inliers);
      plane_extract_indices.setNegative(true);
      plane_extract_indices.filter(*plane_cloud);

      //  ********************************    Object Clustering
      std::vector<pcl::PointIndices> cluster_indices;
      tree->setInputCloud(plane_cloud);

      pcl::EuclideanClusterExtraction<PointT> euclid_extract_cluster;
      euclid_extract_cluster.setClusterTolerance(0.25); // 2cm
      euclid_extract_cluster.setMinClusterSize(600);
      euclid_extract_cluster.setMaxClusterSize(5000);
      euclid_extract_cluster.setSearchMethod(tree);
      euclid_extract_cluster.setInputCloud(plane_cloud);
      euclid_extract_cluster.extract(cluster_indices);

      pcl::PointCloud<PointT>::Ptr all_clusters (new pcl::PointCloud<PointT>);
      
      struct BBox
      {
        float x_min;
        float x_max;
        float y_min;
        float y_max;
        float z_min;
        float z_max;
        double r = 1.0;
        double g = 0.0;
        double b = 0.0;
      };
      std::vector<BBox> bbox_list;

      for (size_t i = 0; i < cluster_indices.size(); i++)
      {
        pcl::PointCloud<PointT>::Ptr each_cluster (new pcl::PointCloud<PointT>);
        pcl::IndicesPtr indices(new std::vector<int>(
          cluster_indices[i].indices.begin(), cluster_indices[i].indices.end()));
        
        //  Extracting from indices
        pcl::ExtractIndices<PointT> extract;
        extract.setInputCloud (plane_cloud);
        extract.setIndices(indices);
        extract.setNegative (false);
        //
        extract.filter(*each_cluster);
        
        all_clusters->operator+=(*each_cluster);

        // adding bbox
        Eigen::Vector4f min_pt, max_pt;
        pcl::getMinMax3D<PointT>(*each_cluster, min_pt, max_pt);
        BBox bbox;
        bbox.x_min = min_pt[0];
        bbox.y_min = min_pt[1];
        bbox.z_min = min_pt[2];
        bbox.x_max = max_pt[0];
        bbox.y_max = max_pt[1];
        bbox.z_max = max_pt[2];
        bbox_list.push_back(bbox);
      }
    
      //  ********************************    Visualization
      visualization_msgs::msg::MarkerArray marker_array;

      int id = 0;
      const std_msgs::msg::Header& inp_header = input_cloud->header;
      // Create a marker for each bounding box
      for (const auto& bbox : bbox_list)
      {
        // Create the marker for the top square
        visualization_msgs::msg::Marker top_square_marker;
        top_square_marker.header = inp_header;
        top_square_marker.ns = "bounding_boxes";
        top_square_marker.id = id++;
        top_square_marker.type = visualization_msgs::msg::Marker::LINE_STRIP;
        top_square_marker.action = visualization_msgs::msg::Marker::ADD;
        top_square_marker.pose.orientation.w = 1.0;
        top_square_marker.scale.x = 0.06;
        top_square_marker.color.r = bbox.r;
        top_square_marker.color.g = bbox.g;
        top_square_marker.color.b = bbox.b;
        top_square_marker.color.a = 1.0;

        // Add the points to the top square marker
        geometry_msgs::msg::Point p1, p2, p3, p4;
        p1.x = bbox.x_max; p1.y = bbox.y_max; p1.z = bbox.z_max;
        p2.x = bbox.x_min; p2.y = bbox.y_max; p2.z = bbox.z_max;
        p3.x = bbox.x_min; p3.y = bbox.y_min; p3.z = bbox.z_max;
        p4.x = bbox.x_max; p4.y = bbox.y_min; p4.z = bbox.z_max;
        top_square_marker.points.push_back(p1);
        top_square_marker.points.push_back(p2);
        top_square_marker.points.push_back(p3);
        top_square_marker.points.push_back(p4);
        top_square_marker.points.push_back(p1);

        // Add the top square marker to the array
        marker_array.markers.push_back(top_square_marker);

        // Create the marker for the bottom square
        visualization_msgs::msg::Marker bottom_square_marker;
        bottom_square_marker.header = inp_header;
        bottom_square_marker.ns = "bounding_boxes";
        bottom_square_marker.id = id++;
        bottom_square_marker.type = visualization_msgs::msg::Marker::LINE_STRIP;
        bottom_square_marker.action = visualization_msgs::msg::Marker::ADD;
        bottom_square_marker.pose.orientation.w = 1.0;
        bottom_square_marker.scale.x = 0.04;
        bottom_square_marker.color.r = bbox.r;
        bottom_square_marker.color.g = bbox.g;
        bottom_square_marker.color.b = bbox.b;
        bottom_square_marker.color.a = 1.0;

        // Add the points to the bottom square marker
        geometry_msgs::msg::Point p5, p6, p7, p8;
        p5.x = bbox.x_max; p5.y = bbox.y_max; p5.z = bbox.z_min;
        p6.x = bbox.x_min; p6.y = bbox.y_max; p6.z = bbox.z_min;
        p7.x = bbox.x_min; p7.y = bbox.y_min; p7.z = bbox.z_min;
        p8.x = bbox.x_max; p8.y = bbox.y_min; p8.z = bbox.z_min;

        bottom_square_marker.points.push_back(p5);
        bottom_square_marker.points.push_back(p6);
        bottom_square_marker.points.push_back(p7);
        bottom_square_marker.points.push_back(p8);
        bottom_square_marker.points.push_back(p5); // connect the last point to the first point to close the square

        // Add the bottom square marker to the marker array
        marker_array.markers.push_back(bottom_square_marker);

        // Create the marker for the lines connecting the top and bottom squares
        visualization_msgs::msg::Marker connecting_lines_marker;
        connecting_lines_marker.header = inp_header;
        connecting_lines_marker.ns = "bounding_boxes";
        connecting_lines_marker.id = id++;
        connecting_lines_marker.type = visualization_msgs::msg::Marker::LINE_LIST;
        connecting_lines_marker.action = visualization_msgs::msg::Marker::ADD;
        connecting_lines_marker.pose.orientation.w = 1.0;
        connecting_lines_marker.scale.x = 0.04;
        connecting_lines_marker.color.r = 0.0;
        connecting_lines_marker.color.g = 1.0;
        connecting_lines_marker.color.b = 0.0;
        connecting_lines_marker.color.a = 1.0;

        // Add the points to the connecting lines marker
        connecting_lines_marker.points.push_back(p1);
        connecting_lines_marker.points.push_back(p5);
        connecting_lines_marker.points.push_back(p2);
        connecting_lines_marker.points.push_back(p6);
        connecting_lines_marker.points.push_back(p3);
        connecting_lines_marker.points.push_back(p7);
        connecting_lines_marker.points.push_back(p4);
        connecting_lines_marker.points.push_back(p8);

        // Add the connecting lines marker to the marker array
        marker_array.markers.push_back(connecting_lines_marker);


        // Create a marker for the corners
        visualization_msgs::msg::Marker corner_marker;
        corner_marker.header = inp_header;
        corner_marker.ns = "bounding_boxes";
        corner_marker.id = id++;
        corner_marker.type = visualization_msgs::msg::Marker::SPHERE;
        corner_marker.action = visualization_msgs::msg::Marker::ADD;
        corner_marker.pose.orientation.w = 1.0;
        corner_marker.scale.x = 0.4;
        corner_marker.scale.y = 0.4;
        corner_marker.scale.z = 0.4;
        corner_marker.color.r = bbox.r;
        corner_marker.color.g = 0.2;
        corner_marker.color.b = 0.5;
        corner_marker.color.a = 0.64;

        // Create a sphere for each corner and add it to the marker array
        corner_marker.pose.position = p1;
        corner_marker.id = id++;
        marker_array.markers.push_back(corner_marker);
        corner_marker.pose.position = p2;
        corner_marker.id = id++;
        marker_array.markers.push_back(corner_marker);
        corner_marker.pose.position = p3;
        corner_marker.id = id++;
        marker_array.markers.push_back(corner_marker);
        corner_marker.pose.position = p4;
        corner_marker.id = id++;
        marker_array.markers.push_back(corner_marker);
        corner_marker.pose.position = p5;
        corner_marker.id = id++;
        marker_array.markers.push_back(corner_marker);
        corner_marker.pose.position = p6;
        corner_marker.id = id++;
        marker_array.markers.push_back(corner_marker);
        corner_marker.pose.position = p7;
        corner_marker.id = id++;
        marker_array.markers.push_back(corner_marker);
        corner_marker.pose.position = p8;
        corner_marker.id = id++;
        marker_array.markers.push_back(corner_marker);

        publisher_marker->publish(marker_array);
      }
      // Convert to ros2 message
      sensor_msgs::msg::PointCloud2 ros2_cluster_cloud;
      pcl::toROSMsg(*all_clusters, ros2_cluster_cloud);
      ros2_cluster_cloud.header = input_cloud->header;

      publisher_->publish(ros2_cluster_cloud);
    }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr publisher_marker;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_;
  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_;

  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<VoxelGrid_filter>());
  rclcpp::shutdown();
  return 0;
}