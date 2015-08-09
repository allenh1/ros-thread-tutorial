#include "RobotThread.h"

RobotThread::RobotThread(int argc, char** pArgv)
    : m_Init_argc(argc),
      m_pInit_argv(pArgv)
{/** Constructor for the robot thread **/}

RobotThread::~RobotThread()
{
    if (ros::isStarted())
    {
        ros::shutdown();
        ros::waitForShutdown();
    }//end if

    m_pThread->wait();
}//end destructor

bool RobotThread::init()
{
    m_pThread = new QThread();
    this->moveToThread(m_pThread);

    connect(m_pThread, &QThread::started, this, &RobotThread::run);

    ros::init(m_Init_argc, m_pInit_argv, "pose_echo_threaded");

    if (!ros::master::check())
        return false;//do not if ros is not running

    ros::start();
    ros::Time::init();
    ros::NodeHandle nh;

    pose_listener = nh.subscribe("odom", 100, &RobotThread::poseCallback, this);
    pose2d_pub = nh.advertise<Pose2D>("/pose2d", 100);
    
    m_pThread->start();
    return true;
}//set up ros

void RobotThread::poseCallback(const nav_msgs::Odometry & msg)
{
    QMutex * pMutex = new QMutex();
    pMutex->lock();
    m_xPos = msg.pose.pose.position.x;
    m_yPos = msg.pose.pose.position.y;
    m_aPos = msg.pose.pose.orientation.w;
    std::printf("Pose: (%.4f, %.4f, %.4f)\n", m_xPos, m_yPos, m_aPos);
    pMutex->unlock();

    delete pMutex;
}//callback method to echo the robot's position

void RobotThread::run()
{
    ros::Rate loop_rate(1000);

    QMutex * pMutex;

    while (ros::ok())
    {
        pMutex = new QMutex();
        pMutex->lock();
        poseMessage.xPose = m_xPos;
        poseMessage.yPose = m_yPos;
        pose2d_pub.publish(poseMessage);\
        pMutex->unlock();

        delete pMutex;

        ros::spinOnce();
        loop_rate.sleep();
    }//run while ROS is ok.
}
