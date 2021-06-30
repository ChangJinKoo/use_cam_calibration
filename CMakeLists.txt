cmake_minimum_required(VERSION 3.0.2)

project(use_cam_calibration)

set(OpenCV_DIR /usr/share/opencv4/)

find_package(OpenCV REQUIRED)

add_executable(use_cam_calibration main.cpp)

target_link_libraries(use_cam_calibration ${OpenCV_LIBS})
