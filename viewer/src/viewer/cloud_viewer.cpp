
#include "viewer/cloud_viewer.hpp"

namespace mylib {

CloudViewer::CloudViewer(const std::string& viewer_name) : cloud_viewer_(new pcl::visualization::PCLVisualizer(viewer_name))
{
  cloud_viewer_->setPosition(0, 0);
  cloud_viewer_->setSize(800, 600);
}

CloudViewer::~CloudViewer()
{
}

void CloudViewer::update(Cloud::Ptr& cloud, const std::string& input="input")
{
  if(!cloud)
    return;

  if(!cloud_viewer_->updatePointCloud(cloud, input))
  {
    cloud_viewer_->addPointCloud(cloud, input);
    cloud_viewer_->addCoordinateSystem(0.1, input);
    cloud_viewer_->resetCameraViewpoint(input);
    cloud_viewer_->setCameraPosition(
      0,0,-2,		// Position
      0,0,1,		// Viewpoint
      0,-1,0);	// Up
  }
}

}
