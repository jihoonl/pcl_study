
#ifndef __COMMON_KEYFRAME_HPP__
#define __COMMON_KEYFRAME_HPP__

#include "typedef.hpp"

namespace mylib {

class Keyframe {
  public:
    Keyframe(Cloud::ConstPtr cloud, ImagePtr image);
    ~Keyframe();
    Cloud::Ptr c;
    ImagePtr i;
};

typedef std::vector<Keyframe> KeyframeVec;
typedef boost::shared_ptr<KeyframeVec> KeyframeVecPtr;

}

#include "impl/keyframe.hpp"

#endif
