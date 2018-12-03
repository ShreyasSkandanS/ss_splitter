#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

image_transport::Publisher l_pub, r_pub;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
	auto cv_ptr = cv_bridge::toCvShare(msg);
	cv::Rect roi_left;
	roi_left.x = 0;
	roi_left.y = 0;
	roi_left.width = 1280;
	roi_left.height = 1024;
	cv::Rect roi_right;
	roi_right.x = 0;
	roi_right.y = 1024;
	roi_right.width = 1280;
	roi_right.height = 1024;
	cv_bridge::CvImage out_left;
	cv_bridge::CvImage out_right;
	out_left.header = cv_ptr->header;
	out_right.header = cv_ptr->header;
	out_left.encoding = cv_ptr->encoding;
	out_right.encoding = cv_ptr->encoding;
	out_left.image = cv_ptr->image(roi_left);
	out_right.image = cv_ptr->image(roi_right);
	l_pub.publish(out_left.toImageMsg());
	r_pub.publish(out_right.toImageMsg());
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not crop image.");
  }
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_cropper");
  ros::NodeHandle nh;

  image_transport::ImageTransport it(nh);

  l_pub = it.advertise("left/image_raw", 1);
  r_pub = it.advertise("right/image_raw", 1);

  ros::Subscriber image_sub = nh.subscribe("image", 1, &imageCallback);

  ros::spin();
}
