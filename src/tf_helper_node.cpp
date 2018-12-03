#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/PointStamped.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "tf_helper");
  ros::NodeHandle nh;
  ros::AsyncSpinner spinner(4);
  spinner.start();
  
  std::string target_frame;
  std::string source_frame;
  if (!nh.getParam("source_frame",source_frame))
  {
    ROS_ERROR("source_frame not exist");
    return 0;
  }
  if (!nh.getParam("target_frame",target_frame))
  {
    ROS_ERROR("target_frame not exist");
    return 0;
  }
  double rate;
  if (!nh.getParam("rate",rate))
  {
    ROS_ERROR("rate not exist");
    return 0;
  }
  ros::Rate lp(rate);
  
  
  tf::TransformListener listener;
  tf::StampedTransform transform;
  ros::Publisher point_pub=nh.advertise<geometry_msgs::PointStamped>("point",1);
  
  while (ros::ok())
  {
    try
    {
      listener.lookupTransform(target_frame, source_frame,  
                              ros::Time(0), transform );
      geometry_msgs::PointStamped pnt;
      pnt.point.x=transform.getOrigin().getX();
      pnt.point.y=transform.getOrigin().getY();
      pnt.point.z=transform.getOrigin().getZ();
      pnt.header.stamp=ros::Time::now();
      point_pub.publish(pnt);
    }
    catch (tf::TransformException ex){
      ROS_DEBUG("%s",ex.what());
    }
    
    lp.sleep();
  }
}