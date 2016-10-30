
#include <pcl/io/openni2_grabber.h>
#include <pcl/visualization/pcl_visualizer.h>

typedef pcl::PointCloud<pcl::PointXYZRGBA> Cloud;
typedef pcl::io::OpenNI2Grabber O2Grabber;
typedef pcl::visualization::PCLVisualizer CloudViewer;

class SimpleViewer
{

  public:
    SimpleViewer()
    {
      grabber_.reset(new O2Grabber());
      viewer_.reset(new CloudViewer("Simple Viewer"));
    }

    void cloud_cb(const Cloud::ConstPtr &cloud)
    {
      if (!viewer_->wasStopped())
      {
        if(!viewer_->updatePointCloud(cloud, "Cloud"))
        {
          viewer_->addPointCloud(cloud, "Cloud");
        }
      }
    }

    void run ()
    {
      boost::function<void (const Cloud::ConstPtr&)> f = boost::bind (&SimpleViewer::cloud_cb, this, _1);

      grabber_->registerCallback (f);
      grabber_->start ();

      while (!viewer_->wasStopped())
      {
        viewer_->spinOnce();
        boost::this_thread::sleep (boost::posix_time::seconds (0.05));
      }

      grabber_->stop ();
    }

    O2Grabber::Ptr grabber_;
    CloudViewer::Ptr viewer_;
};

int main ()
{
  SimpleViewer v;
  v.run ();
  return 0;
}

