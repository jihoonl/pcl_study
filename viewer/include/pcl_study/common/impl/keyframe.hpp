
#ifndef __COMMON_KEYFRAME_IMPL_HPP__
#define __COMMON_KEYFRAME_IMPL_HPP__

#include <pcl/common/io.h>


namespace mylib {

Keyframe::Keyframe(Cloud::ConstPtr cloud, ImagePtr image) : c(new Cloud)
{
  pcl::copyPointCloud(*cloud, *c);
  //i.reset(new Image(image));
  //i = image;
}

Keyframe::~Keyframe() {
}

}

#endif
