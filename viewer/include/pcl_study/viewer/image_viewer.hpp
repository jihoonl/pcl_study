
#ifndef __VIEWER_IMAGE_VIEWER_HPP__
#define __VIEWER_IMAGE_VIEWER_HPP__

#include <pcl/visualization/image_viewer.h>

#include "pcl_study/common/typedef.hpp"

namespace mylib {

class ImageViewer {
  public:
    ImageViewer(const std::string& viewer_name);
    ~ImageViewer();

    void update(ImagePtr& image);

  private:
    boost::shared_ptr<pcl::visualization::ImageViewer> image_viewer_;

};

}
#endif
