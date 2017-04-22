#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui.hpp>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Image.h"

void imageCallback(const sensor_msgs::Image::ConstPtr& msg)
{
	try
	{
		cv::imshow("colorimage", cv_bridge::toCvShare(msg,"bgr8")->image);
		cv::waitKey(10);
	}
	catch(cv_bridge::Exception& e)
	{
		ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
	}
}

int main(int argc, char **argv)
{

  //init scandata ....


  ros::init(argc, argv, "ColorImage_listener");

  ros::NodeHandle n;

  cv::namedWindow("colorimage");
  
  cv::startWindowThread();

  ros::Subscriber sub = n.subscribe("/camera/color/image_raw", 1000, imageCallback);

  ros::spin();
  
  cv::destroyWindow("colorimage");

  return 0;
}
