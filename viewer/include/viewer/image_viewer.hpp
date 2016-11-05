
#ifndef __IMAGE_VIEWER_HPP__
#define __IMAGE_VIEWER_HPP__

#include "typedef.hpp"
#include <pcl/visualization/image_viewer.h>

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
