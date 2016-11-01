

#ifndef __GRABBER_HPP__
#define __GRABBER_HPP__

#include "viewer/typedef.hpp"

class MyGrabber
{
public:
  MyGrabber()
  {
    std::string device_id ("");
    pcl::io::OpenNI2Grabber::Mode depth_mode = pcl::io::OpenNI2Grabber::OpenNI_Default_Mode;
    pcl::io::OpenNI2Grabber::Mode image_mode = pcl::io::OpenNI2Grabber::OpenNI_Default_Mode;
    bool xyz = false;

    boost::shared_ptr<pcl::io::openni2::OpenNI2DeviceManager> deviceManager = pcl::io::openni2::OpenNI2DeviceManager::getInstance ();
    if (deviceManager->getNumOfConnectedDevices () > 0)
    {
      boost::shared_ptr<pcl::io::openni2::OpenNI2Device> device = deviceManager->getAnyDevice ();
      std::cout << "Device ID not set, using default device: " << device->getStringID () << std::endl;
    }
    grabber_ = Grabber::Ptr(new Grabber(device_id, depth_mode, image_mode));
  }

  ~MyGrabber()
  {
    disconnectAll();
  }

  template <typename T>
  void addConnection(boost::function<void (const T&)> cb)
  {
    Connection c = grabber_->registerCallback(cb);
    connections_.push_back(c);
  }

  void disconnectAll()
  {
    unsigned int i = 0;

    for(i=0; i < connections_.size(); ++i)
      connections_[i].disconnect();
  }

  void start()
  {
    grabber_->start();
  }

  void stop()
  {
    grabber_->stop();
  }


private:
  Grabber::Ptr grabber_;
  ConnectionVector connections_;
};

#endif
