
#ifndef __GRABBER_IMPL_HPP__
#define __GRABBER_IMPL_HPP__

#include "pcl_study/grabber/grabber.hpp"

namespace mylib {

MyGrabber::MyGrabber()
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

MyGrabber::~MyGrabber()
{
  disconnectAll();
}

template <typename T>
void MyGrabber::addConnection(boost::function<void (const T&)> cb)
{
  Connection c = grabber_->registerCallback(cb);
  connections_.push_back(c);
}

void MyGrabber::disconnectAll()
{
  unsigned int i = 0;

  for(i=0; i < connections_.size(); ++i)
    connections_[i].disconnect();
}

void MyGrabber::start()
{
  grabber_->start();
}

void MyGrabber::stop()
{
  grabber_->stop();
}

}

#endif
