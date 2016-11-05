
#ifndef __VIEWER_COMPUTE_HPP__
#define __VIEWER_COMPUTE_HPP__

#include "typedef.hpp"
#include "keyframe.hpp"

namespace mylib {

class Compute {

public:
  Compute() {
    //keyframe_.clear();
//    current_frame_.c.reset();
//    current_frame_.i.reset();
    compute_thread_ = boost::thread(&Compute::process, this);
    new_data_available_ = false;
    is_running_ = true;
  }

  ~Compute() {
    new_data_available_ = false;
    is_running_ = false;
    compute_thread_.join();

    keyframe_.clear();
    //frames_.clear();
  }

  void setKeyframe(Cloud::ConstPtr cloud, ImagePtr image)
  {
    boost::mutex::scoped_lock lock (data_mutex_);
    current_cloud_ = cloud;
    current_image_ = image;
    new_data_available_ = true;
  }

  Keyframe getKeyframe()
  {
    boost::mutex::scoped_lock lock (data_mutex_);
    Keyframe k(current_cloud_, current_image_);

    return k;
  }

  void process()
  {
    while(is_running_) {
      if(new_data_available_) {
        Keyframe frame = getKeyframe();
        keyframe_.push_back(frame);
        new_data_available_ = false;
      }
      boost::this_thread::sleep(boost::posix_time::seconds(1));
    }
    for(unsigned int i = 0; i < keyframe_.size(); i++)
    {
      std::cout << *(keyframe_[i].c) << std::endl;
    }
  }

  private:
    boost::mutex data_mutex_;
    Cloud::ConstPtr current_cloud_;
    ImagePtr current_image_;
    bool new_data_available_;
    bool is_running_;
    std::vector<Keyframe> keyframe_;
    boost::thread compute_thread_;
};

}

#endif
