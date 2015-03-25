#include <ros/ros.h>
#include <ros/network.h>
#include <nav_msgs/Odometry.h>
#include <stdio.h>
#include <ros_threading_example/Pose2D.h>

typedef ros_threading_example::Pose2D Pose2D;

Pose2D poseMessage;
void poseCallback(const nav_msgs::Odometry& msg)
{
    float m_xPos = msg.pose.pose.position.x;
    float m_yPos = msg.pose.pose.position.y;
    float m_aPos = msg.pose.pose.orientation.w;

    std::printf("Pose: (%.4f, %.4f, %.4f)\n", m_xPos, m_yPos, m_aPos);
    poseMessage.xPose = m_xPos;
    poseMessage.yPose = m_yPos;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "pose_listener");

  ros::NodeHandle n;

  ros::Rate rate(100);

  ros::Subscriber sub = n.subscribe("odom", 10, poseCallback);
  ros::Publisher  pub = n.advertise<Pose2D>("/pose2d", 100);

  while (ros::ok()) {
  	pub.publish(poseMessage);

  	ros::spinOnce();
  	rate.sleep();
  }
  ros::spin();

  return 0;
}