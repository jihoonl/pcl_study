
#ifndef __VIEWER_KEYFRAME_HPP__
#define __VIEWER_KEYFRAME_HPP__

#include "typedef.hpp"

namespace mylib {

class Keyframe {
  public:
    Keyframe(Cloud::ConstPtr cloud, ImagePtr image) : c(new Cloud), i(image)
    {
      *c = *cloud;
    }

    ~Keyframe() { }

    Cloud::Ptr c;
    ImagePtr i;
};

}

#endif
