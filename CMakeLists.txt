cmake_minimum_required(VERSION 3.5)
project(test CXX)

include_directories(common)
add_subdirectory(common)  

include_directories(modules)
add_subdirectory(modules)  


add_executable(${PROJECT_NAME}
    main.cpp
)
find_package(OpenCV REQUIRED)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS} modules common)