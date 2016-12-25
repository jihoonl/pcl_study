
#include "pcl_study/viewer/viewer.hpp"

namespace mylib {

Viewer::Viewer()
: cloud_viewer_(new pcl::visualization::PCLVisualizer("Cloud Viewer"))
, image_viewer_(new pcl::visualization::ImageViewer("Image Viewer"))
, input_cloud_name_("Input Cloud")
{
    cloud_viewer_->setPosition(0, 0);
    cloud_viewer_->setSize(800, 600);

//    kf_viewer_->setPosition(0, 0);
//  kf_viewer_->setSize(800, 600);//

    image_viewer_->setPosition(800, 0);
    image_viewer_->setSize(800, 600);

}

Viewer::~Viewer()
{}

void Viewer::updateViewer(Cloud::ConstPtr& cloud, ImagePtr& image)
{
  if(cloud) {
    if (!cloud_viewer_->updatePointCloud (cloud, input_cloud_name_.c_str()))
    {
      cloud_viewer_->addPointCloud (cloud, input_cloud_name_.c_str());
      cloud_viewer_->addCoordinateSystem(0.1, input_cloud_name_.c_str());
      cloud_viewer_->resetCameraViewpoint (input_cloud_name_.c_str());
      cloud_viewer_->setCameraPosition (
        0,0,-2,		// Position
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
//    image_viewer_->addRGBImage ( (const unsigned char*)image->getData (), image->getWidth (), image->getHeight ());
    image_viewer_->addRGBImage(*cloud);
  }

  //kf_viewer_->spinOnce();
  cloud_viewer_->spinOnce();
  image_viewer_->spinOnce ();
}

void Viewer::updateViewer(Cloud::Ptr& cloud, ImagePtr& image)
{
  if(cloud) {
    if (!cloud_viewer_->updatePointCloud (cloud, input_cloud_name_.c_str()))
    {
      cloud_viewer_->addPointCloud (cloud, input_cloud_name_.c_str());
      cloud_viewer_->addCoordinateSystem(0.1, input_cloud_name_.c_str());
      cloud_viewer_->resetCameraViewpoint (input_cloud_name_.c_str());
      cloud_viewer_->setCameraPosition (
        0,0,-2,		// Position
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
    //image_viewer_->addRGBImage ( (const unsigned char*)image->getData (), image->getWidth (), image->getHeight ());
    image_viewer_->addRGBImage(*cloud);
  }

  //kf_viewer_->spinOnce();
  cloud_viewer_->spinOnce();
  image_viewer_->spinOnce ();
}
}
