
#ifndef __VIEWER_HPP__
#define __VIEWER_HPP__

#include "typedef.hpp"
#include <pcl/visualization/image_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>

namespace mylib {

class Viewer {

public:
  Viewer();
  ~Viewer();

  void updateViewer(Cloud::ConstPtr& cloud, ImagePtr& image);

protected:
  boost::shared_ptr<pcl::visualization::PCLVisualizer> cloud_viewer_;
  //boost::shared_ptr<pcl::visualization::PCLVisualizer> kf_viewer_;
  boost::shared_ptr<pcl::visualization::ImageViewer> image_viewer_;

  std::string input_cloud_name_;
};
}

#endif
