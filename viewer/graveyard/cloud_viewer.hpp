


#ifndef __CLOUD_VIWER_HPP__
#define __CLOUD_VIWER_HPP__

#include <pcl/visualization/pcl_visualizer.h>
#include "viewer_control.hpp"

template <typename PointType>
class CloudViewer : public ViewerControl
{
public:
  CloudViewer(pcl::io::OpenNI2Grabber::Ptr grabber)
    : ViewerControl(grabber)
    , cloud_viewer_(new pcl::visualization::PCLVisualizer("PCL Viewer")
  {
    boost::function<void (const CloudConstPtr&) > cloud_cb = boost::bind (&CloudViewer::cloud_callback, this, _1);
    boost::signals2::connection cloud_connection = grabber_->registerCallback (cloud_cb);
  }

  void cloud_callback (const CloudConstPtr& cloud)
  {
    //FPS_CALC ("cloud callback");
    boost::mutex::scoped_lock lock (cloud_mutex_);
    cloud_ = cloud;
  }

  CloudConstPtr cloud_;
  boost::shared_ptr<pcl::visualization::PCLVisualizer> cloud_viewer_;
  boost::mutex cloud_mutex_;
}

#endif
