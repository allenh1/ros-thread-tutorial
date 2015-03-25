cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_BUILD_TYPE DEBUG)
project(ros_threading_example)
find_package(catkin REQUIRED COMPONENTS roscpp message_generation)
find_package(Qt5Widgets)
find_package(Qt5Core)

add_message_files(FILES Pose2D.msg)
generate_messages(DEPENDENCIES std_msgs)

catkin_package(
  CATKIN_DEPENDS roscpp geometry_msgs message_generation
  DEPENDS system-lib
)

file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
    FOLLOW_SYMLINKS src/*.h)
    
qt5_wrap_cpp(QT_MOC_HPP ${QT_MOC})

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    FOLLOW_SYMLINKS src/*.cpp)

include_directories(src ${catkin_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})

add_executable(pose_echo_threaded ${QT_SOURCES} ${QT_RESOURCES_CPP}
              ${QT_MOC_HPP})
add_executable(pose_echo src/PoseEcho.cc)

add_dependencies(pose_echo ${PROJECT_NAME}_generate_messages_cpp)
add_dependencies(pose_echo_threaded ${PROJECT_NAME}_generate_messages_cpp)

target_link_libraries(pose_echo_threaded ${QT_LIBRARIES}
            		  ${catkin_LIBRARIES} Qt5::Widgets)
target_link_libraries(pose_echo ${catkin_LIBRARIES} Qt5::Widgets)

install(TARGETS pose_echo_threaded pose_echo
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
