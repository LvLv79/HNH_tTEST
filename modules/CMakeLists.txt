cmake_minimum_required(VERSION 3.15)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenCV 4 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

aux_source_directory(A1 A1_src)
aux_source_directory(A2 A2_src)
aux_source_directory(M1 M1_src)
aux_source_directory(M2 M2_src)

add_library(modules OBJECT ${A1_src} ${A2_src} ${M1_src} ${M2_src})
target_link_libraries(modules ${OpenCV_LIBS}) 