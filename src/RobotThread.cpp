#include "RobotThread.h"

RobotThread::RobotThread(int argc, char** pArgv, const char * topic)
    : m_Init_argc(argc),
        m_pInit_argv(pArgv),
        m_topic(topic)
{/** Constructor for the robot thread **/}

RobotThread::~RobotThread()
{
    if (ros::isStarted())
    {
        ros::shutdown();
        ros::waitForShutdown();
    }//end if

    wait();
}//end destructor

bool RobotThread::init()
{
    ros::init(m_Init_argc, m_pInit_argv, "gui_command");

    if (!ros::master::check())
        return false;//do not if ros is not running

    ros::start();
    ros::Time::init();
    ros::NodeHandle nh;

    pose_listener = nh.subscribe(m_topic, 10, &RobotThread::poseCallback, this);
    start();
    return true;
}//set up the ros toys.

void RobotThread::poseCallback(nav_msgs::Odometry msg)
{
    float m_xPos = msg.pose.pose.position.x;
    float m_yPos = msg.pose.pose.position.y;
    float m_aPos = msg.pose.pose.orientation.w;

    ROS_INFO("Pose: (%f, %f, %f)", m_xPos, m_yPos, m_aPos);
}//callback method to echo the robot's position

void RobotThread::run()
{
    ros::Rate loop_rate(1);
    while (ros::ok())
    {
        ros::spinOnce();
        loop_rate.sleep();
    }//run while ROS is ok.
}