#ifndef ROBOTTHREAD_H
#define ROBOTTHREAD_H

#include <iostream>
#include <stdio.h>

#include <QString>
#include <QThread>

#include <ros/ros.h>
#include <ros/network.h>
#include <nav_msgs/Odometry.h>
#include <ros_threading_example/Pose2D.h>

typedef ros_threading_example::Pose2D Pose2D;

class RobotThread : public QThread {
  Q_OBJECT
public:
  RobotThread(int argc, char **argv);
  virtual ~RobotThread();

  bool init();
  void run();

  void poseCallback(nav_msgs::Odometry msg);

private:
  int m_Init_argc;
  char ** m_pInit_argv;

  double m_xPos;
  double m_yPos;
  double m_aPos;

  const char * m_topic;

  Pose2D poseMessage;

  ros::Subscriber pose_listener;
  ros::Publisher  pose2d_pub;
};
#endif