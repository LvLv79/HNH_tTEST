cmake_minimum_required(VERSION 3.15)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenCV 4 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

aux_source_directory(kalman kalman_src)
aux_source_directory(math math_src)

add_library(common OBJECT ${kalman_src} ${math_src})
target_link_libraries(common ${OpenCV_LIBS})