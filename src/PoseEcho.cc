#include <ros/ros.h>
#include <ros/network.h>
#include <nav_msgs/Odometry.h>

void poseCallback(const nav_msgs::Odometry& msg)
{
    float m_xPos = msg.pose.pose.position.x;
    float m_yPos = msg.pose.pose.position.y;
    float m_aPos = msg.pose.pose.orientation.w;

    ROS_INFO("Pose: (%f, %f, %f)", m_xPos, m_yPos, m_aPos);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "pose_listener");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("odom", 1000, poseCallback);

  ros::spin();

  return 0;
}