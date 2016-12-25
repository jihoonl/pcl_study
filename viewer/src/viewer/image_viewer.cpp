
#include "pcl_study/viewer/image_viewer.hpp"

namespace mylib {

ImageViewer::ImageViewer(const std::string& viewer_name) : image_viewer_(new pcl::visualization::ImageViewer(viewer_name))
{
  image_viewer_->setPosition(800, 0);
  image_viewer_->setSize(800, 600);
}

ImageViewer::~ImageViewer()
{
  image_viewer_.reset();
}

void ImageViewer::update(ImagePtr& image)
{
  if(!image)
    return;

//  image_viewer_->addRGBImage ( (const unsigned char*)image->getData (), image->getWidth (), image->getHeight ());
  image_viewer_->spinOnce();
}

}
