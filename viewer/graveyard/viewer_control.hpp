#ifndef __VIEWER_CONTROL_HPP__
#define __VIEWER_CONTROL_HPP__

#define MEASURE_FUNCTION_TIME

#include <boost/chrono.hpp>
#include <pcl/common/time.h> //fps calculations

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

class ViewerControl
{
protected:
  ViewerControl()
  {
    //cloud_viewer_->registerMouseCallback (&ViewerControl::mouse_callback, *this);
    //cloud_viewer_->registerKeyboardCallback (&ViewerControl::keyboard_callback, *this);
    //cloud_viewer_->setCameraFieldOfView (1.02259994f);
  }

  ~ViewerControl() {}

  void keyboard_callback (const pcl::visualization::KeyboardEvent& event, void*)
  {
    if (event.getKeyCode ())
      cout << "the key \'" << event.getKeyCode () << "\' (" << event.getKeyCode () << ") was";
    else
      cout << "the special key \'" << event.getKeySym () << "\' was";
    if (event.keyDown ())
      cout << " pressed" << endl;
    else
      cout << " released" << endl;
  }

  void mouse_callback (const pcl::visualization::MouseEvent& mouse_event, void*)
  {
    if (mouse_event.getType () == pcl::visualization::MouseEvent::MouseButtonPress && mouse_event.getButton () == pcl::visualization::MouseEvent::LeftButton)
    {
      cout << "left button pressed @ " << mouse_event.getX () << " , " << mouse_event.getY () << endl;
    }
  }

};

#endif
