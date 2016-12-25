
#ifndef __COMMON_TYPEDEF_HPP__
#define __COMMON_TYPEDEF_HPP__

#include <iostream>
#include <vector>
#include <boost/chrono.hpp>
//#include <boost/thread.hpp>
#include <pcl/visualization/boost.h>
#include "pcl/io/openni2/openni.h"
#include <pcl/io/openni2_grabber.h>
#include <pcl/common/time.h> //fps calculations
#include <pcl/common/common.h>
#include <pcl/PCLImage.h>

namespace mylib {

  typedef pcl::io::OpenNI2Grabber Grabber;
  typedef boost::signals2::connection Connection;
  typedef boost::shared_ptr<Connection> ConnectionPtr;
  typedef std::vector<Connection> ConnectionVector;
  typedef std::vector<ConnectionPtr> ConnectionPtrVector;
  typedef typename pcl::PointCloud<pcl::PointXYZRGBA> Cloud;
  typedef boost::shared_ptr<pcl::io::openni2::Image> ImagePtr;
  typedef boost::chrono::high_resolution_clock HRClock;

  #define SHOW_FPS 1
  #if SHOW_FPS
  #define FPS_CALC(_WHAT_) \
    do \
  { \
    static unsigned count = 0;\
    static double last = pcl::getTime ();\
    double now = pcl::getTime (); \
    ++count; \
    if (now - last >= 1.0) \
  { \
    std::cout << "Average framerate ("<< _WHAT_ << "): " << double (count)/double (now - last) << " Hz" <<  std::endl; \
    count = 0; \
    last = now; \
  } \
  }while (false)
  #else
  #define FPS_CALC (_WHAT_) \
    do \
  { \
  }while (false)
  #endif

}

#endif
