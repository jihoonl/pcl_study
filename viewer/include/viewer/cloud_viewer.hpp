
#ifndef __CLOUD_VIEWER_HPP__
#define __CLOUD_VIEWER_HPP__

#include "typedef.hpp"
#include <pcl/visualization/pcl_visualizer.h>

namespace mylib {

class CloudViewer {
  public:
    CloudViewer(const std::string& viewer_name);
    ~CloudViewer();

    void update(Cloud::ConstPtr& cloud, const std::string& input);

  private:
    boost::shared_ptr<pcl::visualization::PCLVisualizer> cloud_viewer_;

};
}

#endif
