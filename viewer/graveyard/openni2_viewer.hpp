
#ifndef __OPENNI2_VIEWER_HPP__
#define __OPENNI2_VIEWER_HPP__




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointType>
class OpenNI2Viewer
{
public:
  typedef pcl::PointCloud<PointType> Cloud;
  typedef typename Cloud::ConstPtr CloudConstPtr;

  OpenNI2Viewer (pcl::io::OpenNI2Grabber::Ptr grabber)
    : cloud_viewer_ (new pcl::visualization::PCLVisualizer ("PCL OpenNI2 cloud"))
    , image_viewer_ ()
    , grabber_ (grabber)
    , rgb_data_ (0), rgb_data_size_ (0)
  {
  }

  /**
  * @brief starts the main loop
  */
  void run ()
  {
    bool image_init = false, cloud_init = false;

    grabber_->start ();

    while (!cloud_viewer_->wasStopped () && (image_viewer_ && !image_viewer_->wasStopped ()))
    {
      boost::shared_ptr<pcl::io::openni2::Image> image;
      CloudConstPtr cloud;

      cloud_viewer_->spinOnce ();

      // See if we can get a cloud
      if (cloud_mutex_.try_lock ())
      {
        cloud_.swap (cloud);
        cloud_mutex_.unlock ();
      }

      if (cloud)
      {
        //FPS_CALC("drawing cloud");

        if (!cloud_init)
        {
          cloud_viewer_->setPosition (0, 0);
          cloud_viewer_->setSize (cloud->width, cloud->height);
          cloud_init = !cloud_init;
        }

        if (!cloud_viewer_->updatePointCloud (cloud, "OpenNICloud"))
        {
          cloud_viewer_->addPointCloud (cloud, "OpenNICloud");
          cloud_viewer_->resetCameraViewpoint ("OpenNICloud");
          cloud_viewer_->setCameraPosition (
            0,0,0,		// Position
            0,0,1,		// Viewpoint
            0,-1,0);	// Up
        }
      }

      // See if we can get an image
      if (image_mutex_.try_lock ())
      {
        image_.swap (image);
        image_mutex_.unlock ();
      }


      if (image)
      {
        if (!image_init && cloud && cloud->width != 0)
        {
          image_viewer_->setPosition (cloud->width, 0);
          image_viewer_->setSize (cloud->width, cloud->height);
          image_init = !image_init;
        }

        if (image->getEncoding () == pcl::io::openni2::Image::RGB)
          image_viewer_->addRGBImage ( (const unsigned char*)image->getData (), image->getWidth (), image->getHeight ());
        else
          image_viewer_->addRGBImage (rgb_data_, image->getWidth (), image->getHeight ());
        image_viewer_->spinOnce ();

      }
    }

    grabber_->stop ();

    cloud_connection.disconnect ();
    image_connection.disconnect ();
    if (rgb_data_)
      delete[] rgb_data_;
  }

};

#endif
