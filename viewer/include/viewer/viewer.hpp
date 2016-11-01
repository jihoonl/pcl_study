
#ifndef __VIEWER_HPP__
#define __VIEWER_HPP__

#include "typedef.hpp"
#include <pcl/visualization/image_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>

class Viewer {

public:
  Viewer()
  : cloud_viewer_(new pcl::visualization::PCLVisualizer("Cloud Viewer")),
    image_viewer_(new pcl::visualization::ImageViewer("Image Viewer")),
    input_cloud_name_("Input Cloud")
  {
    cloud_viewer_->setPosition(0, 0);
    cloud_viewer_->setSize(640, 480);

    image_viewer_->setPosition(640, 0);
    image_viewer_->setSize(640, 480);

  }
  ~Viewer() {}

  void updateViewer(Cloud::ConstPtr& cloud, ImagePtr& image)
  {
    if(cloud) {
      if (!cloud_viewer_->updatePointCloud (cloud, input_cloud_name_.c_str()))
      {
        cloud_viewer_->addPointCloud (cloud, input_cloud_name_.c_str());
        cloud_viewer_->resetCameraViewpoint (input_cloud_name_.c_str());
        cloud_viewer_->setCameraPosition (
          0,0,0,		// Position
          0,0,1,		// Viewpoint
          0,-1,0);	// Up
      }
    }

    if(image) {
      image_viewer_->addRGBImage ( (const unsigned char*)image->getData (), image->getWidth (), image->getHeight ());
    }
  }

  void viewerSpinOnce()
  {
    cloud_viewer_->spinOnce();
    image_viewer_->spinOnce ();
  }

protected:
  boost::shared_ptr<pcl::visualization::PCLVisualizer> cloud_viewer_;
  boost::shared_ptr<pcl::visualization::ImageViewer> image_viewer_;

  std::string input_cloud_name_;
};

#endif
