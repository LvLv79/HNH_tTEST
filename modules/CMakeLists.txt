cmake_minimum_required(VERSION 3.15)

#set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
#find_package(OpenCV 4 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

#aux_source_directory(A1 A1_src)
#aux_source_directory(A2 A2_src)
#aux_source_directory(M1 M1_src)
#aux_source_directory(M2 M2_src)
#file(GLOB_RECURSE A1_src RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/A1 "*.cpp")

set(MODULE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/A1/include 
${CMAKE_CURRENT_SOURCE_DIR}/A2/include 
${CMAKE_CURRENT_SOURCE_DIR}/M1/include 
${CMAKE_CURRENT_SOURCE_DIR}/M2/include 
CACHE PATH "module include directories")

#message(STATUS ${kalman_INCLUDE_DIRS})
include_directories(${MODULE_INCLUDE_DIRS} ${kalman_INCLUDE_DIRS})

file(GLOB_RECURSE AX_src RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")

add_library(modules OBJECT ${AX_src})
target_link_libraries(modules ${OpenCV_LIBS}) 