cmake_minimum_required(VERSION 2.8.3)
project(ss_splitter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp cv_bridge image_transport)

## Declare a catkin package
catkin_package()

# Find and add OpenCV to libraries
find_package(OpenCV 3 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
message(STATUS ${OpenCV_INCLUDE_DIRS})
message(STATUS ${OpenCV_LIBRARY_DIRS})
message(STATUS ${OpenCV_LIBS})

# Include CATKIN packages
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(split_image src/splitter.cpp)

target_link_libraries(split_image ${catkin_LIBRARIES}
                               ${OpenCV_LIBS})
