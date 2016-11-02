
#ifndef __VIEWER_COMPUTE_HPP__
#define __VIEWER_COMPUTE_HPP__

#include "typedef.hpp"

namespace mylib {

class Compute {

public:
  Compute() {
    keyframe_.clear();
//    current_frame_.c.reset();
    current_frame_.i.reset();
    compute_thread_ = boost::thread(&Compute::process, this);
    new_data_available_ = false;
    is_running_ = true;
  }

  ~Compute() {
    new_data_available_ = false;
    is_running_ = false;
    compute_thread_.join();

    keyframe_.clear();
  }

  void setKeyframe(Cloud::Ptr cloud, ImagePtr image)
  {
    boost::mutex::scoped_lock lock (data_mutex_);
    //current_frame_.c = cloud;
    //pcl::copyPointCloud(*cloud, *(current_frame_.c));//*(current_frame_.c) = *cloud;
    //current_frame_.i = *image;
    new_data_available_ = true;
  }

  Keyframe getKeyframe()
  {
    boost::mutex::scoped_lock lock (data_mutex_);
    Keyframe k;

    k = current_frame_;
    return k;
  }

  void process()
  {
    while(is_running_) {
      if(new_data_available_) {
        Keyframe k = getKeyframe();
        keyframe_.push_back(k);
        std::cout << "Keyframe size " << keyframe_.size() << std::endl;
        new_data_available_ = false;
      }
      boost::this_thread::sleep(boost::posix_time::seconds(1));
    }
  }

  private:
    boost::mutex data_mutex_;
    bool new_data_available_;
    bool is_running_;
    Keyframe current_frame_;
    std::vector<Keyframe> keyframe_;
    boost::thread compute_thread_;
};

}

#endif
