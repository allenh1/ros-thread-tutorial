#ifndef ROBOTTHREAD_H
#define ROBOTTHREAD_H

#include <iostream>
#include <QThread>

#include <ros/ros.h>
#include <ros/network.h>
#include <nav_msgs/Odometry.h>

class RobotThread : public QThread {
  Q_OBJECT
public:
  RobotThread(int argc, char **argv, const char * topic = "/odom");
  virtual ~RobotThread();

  bool init();
  void run();

  void poseCallback(nav_msgs::Odometry msg);

private:
  int m_Init_argc;
  char ** m_pInit_argv;
  const char * m_topic;
  ros::Subscriber pose_listener;
};
#endif