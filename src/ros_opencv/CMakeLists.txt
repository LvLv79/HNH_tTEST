cmake_minimum_required(VERSION 3.5)
project(ros_opencv)
set(OpenCV_DIR /usr/share/OpenCV/)
set(OpenCV_DIR /path/to/opencv/build)
find_package(OpenCV REQUIRED)
## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  OpenCV
  cv_bridge
  geometry_msgs
  roscpp
  sensor_msgs
  std_msgs
  visualization_msgs
)
find_package(OpenCV REQUIRED)
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES ros_opencv
#  CATKIN_DEPENDS OpenCV cv_bridge geometry_msgs roscpp sensor_msgs std_msgs visualization_msgs
#  DEPENDS system_lib
)


include_directories(
include
  ${catkin_INCLUDE_DIRS}
)

add_library(camera
   src/Armor/ArmorDetect.cpp
   src/Pose/AngleSolver.cpp
   src/Camera/Camera.cpp
   src/Armor/ArmorDetect.hpp
   src/Pose/AngleSolver.hpp
   src/Camera/Camera.hpp
)

target_link_libraries(camera
   ${catkin_LIBRARIES} ${OpenCV_LIBS}
)


add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME}
   ${catkin_LIBRARIES} ${OpenCV_LIBS} camera
)


