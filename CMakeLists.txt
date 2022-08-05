# 在此处进行 CMake 设置（最小版本号，项目名）
cmake_minimum_required(VERSION 3.15)

project(HNH CXX)

add_compile_options(-std=c++14)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

####### 以下禁止修改 #######
add_subdirectory(common)   #
add_subdirectory(modules)  #
####### 以上禁止修改 #######

# 在此处生成可执行程序
find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# 在此处链接库
include_directories(${MODULE_INCLUDE_DIRS} ${kalman_INCLUDE_DIRS} ${math_INCLUDE_DIRS})

#message(STATUS ${MODULE_INCLUDE_DIRS})

add_library(common OBJECT common/math/src/Math.cpp)
#target_include_directories(common PUBLIC ${math_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
    main.cpp
)
target_include_directories(${PROJECT_NAME} 
    PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS}
    common
    modules)