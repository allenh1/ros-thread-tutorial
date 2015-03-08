cmake_minimum_required(VERSION 2.8.3)
project(ros_threading_example)
find_package(catkin REQUIRED COMPONENTS qt_build roscpp)

catkin_package(
  CATKIN_DEPENDS roscpp geometry_msgs
  DEPENDS system-lib
)
rosbuild_prepare_qt4(QtCore QtGui)

file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
    FOLLOW_SYMLINKS src/*.h)
    
QT4_WRAP_CPP(QT_MOC_HPP ${QT_MOC})

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    FOLLOW_SYMLINKS src/*.cpp)

include_directories(src ${catkin_INCLUDE_DIRS})

add_executable(pose_echo_threaded ${QT_SOURCES} ${QT_RESOURCES_CPP}
              ${QT_MOC_HPP})
add_executable(pose_echo src/PoseEcho.cc)
target_link_libraries(pose_echo_threaded ${QT_LIBRARIES}
            		  ${catkin_LIBRARIES})
target_link_libraries(pose_echo ${catkin_LIBRARIES})
install(TARGETS pose_echo_threaded pose_echo
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
