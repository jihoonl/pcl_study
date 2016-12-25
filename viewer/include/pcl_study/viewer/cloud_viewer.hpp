
#ifndef __VIEWER_CLOUD_VIEWER_HPP__
#define __VIEWER_CLOUD_VIEWER_HPP__

#include <pcl/visualization/pcl_visualizer.h>

#include "pcl_study/common/typedef.hpp"

namespace mylib {

class CloudViewer {
  public:
    CloudViewer(const std::string& viewer_name);
    ~CloudViewer();

    void update(Cloud::Ptr& cloud, const std::string& input);

  private:
    boost::shared_ptr<pcl::visualization::PCLVisualizer> cloud_viewer_;

};
}

#endif
