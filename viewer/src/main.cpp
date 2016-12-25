
//#include "viewer/openni2_viewer.hpp"
#include "pcl_study/common/typedef.hpp"
#include "pcl_study/common/compute.hpp"
#include "pcl_study/grabber//grabber.hpp"
#include "pcl_study/viewer/viewer.hpp"
#include "pcl_study/common/keyframe.hpp"

namespace mylib {

class Runner : public Viewer {

public:
  Runner() : Viewer()
  {
    grabber_.reset(new MyGrabber());
    compute_.reset(new Compute());
  }

  ~Runner() {
    grabber_.reset();
    compute_.reset();
  }

  void addConnection()
  {
    boost::function<void (const ImagePtr&) > image_cb = boost::bind (&Runner::image_cb, this, _1);
    boost::function<void (const Cloud::ConstPtr&) > cloud_cb = boost::bind (&Runner::cloud_cb, this, _1);
    grabber_->addConnection(image_cb);
    grabber_->addConnection(cloud_cb);
  }

  void removeConnection()
  {
    grabber_->disconnectAll();
  }

  void run()
  {
    addConnection();

    /*
    grabber_->start();

    while (!cloud_viewer_->wasStopped () && (image_viewer_ && !image_viewer_->wasStopped ()))
    {
      ImagePtr image;
      Cloud::ConstPtr cloud;

      cloud = getCloud();
      image = getImage();

//      compute_->setKeyframe(cloud, image);

      updateViewer(cloud, image);
    }
    */

    /*
    KeyframeVecPtr p = compute_->getKeyvector();

    for(unsigned int i = 0; i < p->size(); i++)
    {
      std::cout << "i = " << i << std::endl;
      Keyframe k = p->at(i);
      updateViewer(k.c, k.i);
      boost::this_thread::sleep(boost::posix_time::seconds(0.1));
    }
    */

    removeConnection();
    //grabber_->stop ();

  }

protected:

  Cloud::ConstPtr getCloud()
  {
    Cloud::ConstPtr cloud;

    // See if we can get a cloud
    if (cloud_mutex_.try_lock ())
    {
      cloud_.swap (cloud);
      cloud_mutex_.unlock();
    }
    return cloud;
  }

  ImagePtr getImage()
  {
    ImagePtr image;

    // See if we can get an image
    if (image_mutex_.try_lock ())
    {
      image_.swap (image);
      image_mutex_.unlock ();
    }

    return image;
  }

  void cloud_cb(const Cloud::ConstPtr& cloud)
  {
    //FPS_CALC ("cloud callback");
    boost::mutex::scoped_lock lock (cloud_mutex_);
    cloud_ = cloud;
  }

  void image_cb(const ImagePtr& image)
  {
    //FPS_CALC ("image callback");
    boost::mutex::scoped_lock lock (image_mutex_);
    image_ = image;

    /*
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
      std::cout << "Here" << std::endl;
    }
    */
  }

protected:
  boost::shared_ptr<Compute> compute_;
  boost::shared_ptr<MyGrabber> grabber_;

  Cloud::ConstPtr cloud_;
  ImagePtr image_;
  boost::mutex cloud_mutex_;
  boost::mutex image_mutex_;
  unsigned char* rgb_data_;
  unsigned rgb_data_size_;
};

}

int main (int argc, char** argv)
{
  boost::shared_ptr<mylib::Runner> r(new mylib::Runner());
  std::cout << "Initialised" << std::endl;
  r->run();
  std::cout << "Bye Bye" << std::endl;
  r.reset();
  return 0;
}
