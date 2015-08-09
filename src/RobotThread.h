#ifndef ROBOTTHREAD_H
#define ROBOTTHREAD_H

#include <stdio.h>

#include <QtCore>
#include <QString>
#include <QObject>
#include <QMutex>

#include <ros/ros.h>
#include <ros/network.h>
#include <nav_msgs/Odometry.h>
#include <ros_threading_example/Pose2D.h>

typedef ros_threading_example::Pose2D Pose2D;

class RobotThread : public QObject {
  Q_OBJECT
public:
  RobotThread(int argc, char **argv);
  virtual ~RobotThread();

  bool init();
  Q_SLOT void run();

  void poseCallback(const nav_msgs::Odometry & msg);
private:
  int m_Init_argc;
  char ** m_pInit_argv;

  double m_xPos;
  double m_yPos;
  double m_aPos;

  const char * m_topic;

  Pose2D poseMessage;

  QThread * m_pThread;

  ros::Subscriber pose_listener;
  ros::Publisher  pose2d_pub;
};
#endif