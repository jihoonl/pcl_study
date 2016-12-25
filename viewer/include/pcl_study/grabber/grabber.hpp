

#ifndef __GRABBER_HPP__
#define __GRABBER_HPP__

#include "pcl_study/common/typedef.hpp"

namespace mylib {

class MyGrabber
{
public:
  MyGrabber();
  ~MyGrabber();

  template <typename T>
  void addConnection(boost::function<void (const T&)> cb);

  void disconnectAll();
  void start();
  void stop();

private:
  Grabber::Ptr grabber_;
  ConnectionVector connections_;
};
}

#include "impl/grabber.hpp"

#endif
