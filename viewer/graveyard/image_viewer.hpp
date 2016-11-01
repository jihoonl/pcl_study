
#ifndef __IMAGE_VIEWER_HPP__
#define __IMAGE_VIEWER_HPP__

#include <pcl/visualization/image_viewer.h>
#include "viewer_control.hpp"

template <typename PointType>
class ImageViewer : public ViewerControl
{
public:
  ImageViewer(pcl::io::OpenNI2Grabber::Ptr grabber)
  : ViewerControl(grabber)
  {
    boost::signals2::connection image_connection;
    if (grabber_->providesCallback<void (const boost::shared_ptr<pcl::io::openni2::Image>&)>())
    {
      image_viewer_.reset (new pcl::visualization::ImageViewer ("PCL OpenNI image"));
      image_viewer_->registerMouseCallback (&OpenNI2Viewer::mouse_callback, *this);
      image_viewer_->registerKeyboardCallback (&OpenNI2Viewer::keyboard_callback, *this);
      boost::function<void (const boost::shared_ptr<pcl::io::openni2::Image>&) > image_cb = boost::bind (&OpenNI2Viewer::image_callback, this, _1);
      image_connection = grabber_->registerCallback (image_cb);
    }
  }

protected:
  void image_callback (const boost::shared_ptr<pcl::io::openni2::Image>& image)
  {
    //FPS_CALC ("image callback");
    boost::mutex::scoped_lock lock (image_mutex_);
    image_ = image;

    if (image->getEncoding () != pcl::io::openni2::Image::RGB)
    {
      if (rgb_data_size_ < image->getWidth () * image->getHeight ())
      {
        if (rgb_data_)
          delete [] rgb_data_;
        rgb_data_size_ = image->getWidth () * image->getHeight ();
        rgb_data_ = new unsigned char [rgb_data_size_ * 3];
      }
      image_->fillRGB (image_->getWidth (), image_->getHeight (), rgb_data_);
    }
  }

  boost::shared_ptr<pcl::io::openni2::Image> image_;
  boost::shared_ptr<pcl::visualization::ImageViewer> image_viewer_;
  boost::mutex image_mutex_;
  unsigned char* rgb_data_;
  unsigned rgb_data_size_;
};

#endif
