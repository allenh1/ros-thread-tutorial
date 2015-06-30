cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_BUILD_TYPE RELEASE)
project(ros_threading_example)
find_package(catkin REQUIRED COMPONENTS roscpp
						    message_generation
						              nav_msgs)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)

add_message_files(FILES Pose2D.msg)
generate_messages(DEPENDENCIES std_msgs)

catkin_package(
  CATKIN_DEPENDS roscpp message_generation
  DEPENDS system-lib
)
    
qt5_wrap_cpp(QT_MOC_HPP src/RobotThread.h)

include_directories(src ${catkin_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})

add_executable(pose_echo_threaded src/main.cpp 
								  src/RobotThread.cpp
								  ${QT_RESOURCES_CPP}
              					  ${QT_MOC_HPP})

add_executable(pose_echo src/PoseEcho.cc)

add_dependencies(pose_echo ${PROJECT_NAME}_generate_messages_cpp)
add_dependencies(pose_echo_threaded ${PROJECT_NAME}_generate_messages_cpp)

target_link_libraries(pose_echo_threaded ${catkin_LIBRARIES} Qt5::Widgets)
target_link_libraries(pose_echo ${catkin_LIBRARIES})

install(TARGETS pose_echo_threaded pose_echo
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
