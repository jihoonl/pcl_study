
#ifndef __VIEWER_HPP__
#define __VIEWER_HPP__

#include "typedef.hpp"
#include <pcl/visualization/image_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>

namespace mylib {

class Viewer {

public:
  Viewer()
  : cloud_viewer_(new pcl::visualization::PCLVisualizer("Cloud Viewer")),
//    kf_viewer_(new pcl::visualization::PCLVisualizer("Keyframe Viewer")),
    image_viewer_(new pcl::visualization::ImageViewer("Image Viewer")),
    input_cloud_name_("Input Cloud")
  {
    cloud_viewer_->setPosition(0, 0);
    cloud_viewer_->setSize(800, 600);

//    kf_viewer_->setPosition(0, 0);
//  kf_viewer_->setSize(800, 600);//

    image_viewer_->setPosition(800, 0);
    image_viewer_->setSize(800, 600);

  }
  ~Viewer() {}

  void updateViewer(Cloud::Ptr& cloud, ImagePtr& image)
  {
    if(cloud) {
      if (!cloud_viewer_->updatePointCloud (cloud, input_cloud_name_.c_str()))
      {
        cloud_viewer_->addPointCloud (cloud, input_cloud_name_.c_str());
        cloud_viewer_->addCoordinateSystem(0.1, input_cloud_name_.c_str());
        cloud_viewer_->resetCameraViewpoint (input_cloud_name_.c_str());
        cloud_viewer_->setCameraPosition (
          0,0,0,		// Position
          0,0,1,		// Viewpoint
          0,-1,0);	// Up
      }

      /*
      if (!kf_viewer_->updatePointCloud (cloud, input_cloud_name_.c_str()))
      {
        kf_viewer_->addPointCloud (cloud, input_cloud_name_.c_str());
        kf_viewer_->resetCameraViewpoint (input_cloud_name_.c_str());
        kf_viewer_->setCameraPosition (
          0,0,0,		// Position
          0,0,1,		// Viewpoint
          0,-1,0);	// Up
      }
      */

    }

    if(image) {
      image_viewer_->addRGBImage ( (const unsigned char*)image->getData (), image->getWidth (), image->getHeight ());
    }

    //kf_viewer_->spinOnce();
    cloud_viewer_->spinOnce();
    image_viewer_->spinOnce ();

  }

protected:
  boost::shared_ptr<pcl::visualization::PCLVisualizer> cloud_viewer_;
  //boost::shared_ptr<pcl::visualization::PCLVisualizer> kf_viewer_;
  boost::shared_ptr<pcl::visualization::ImageViewer> image_viewer_;

  std::string input_cloud_name_;
};
}

#endif
