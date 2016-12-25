
#ifndef __COMMON_COMPUTE_HPP__
#define __COMMON_COMPUTE_HPP__

#include "typedef.hpp"
#include "keyframe.hpp"

namespace mylib {

class Compute {

public:
  Compute();
  ~Compute();
  void setKeyframe(Cloud::ConstPtr cloud, ImagePtr image);
  Keyframe getKeyframe();
  void process();
  KeyframeVecPtr getKeyvector();

  private:
    boost::mutex data_mutex_;
    Cloud::ConstPtr current_cloud_;
    ImagePtr current_image_;
    bool new_data_available_;
    bool is_running_;
    KeyframeVecPtr keyframe_;
    boost::thread compute_thread_;
};

}

#include "impl/compute.hpp"

#endif
