cmake_minimum_required(VERSION 2.8)

project(effective-opencv)

# set(OpenCV_DIR "/usr/local/opencv331/share/OpenCV")
set(OpenCV_DIR "/opt/ros/kinetic/share/OpenCV-3.3.1-dev")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(MatTraversal MatTraversal.cpp)
add_subdirectory(Harris)
add_subdirectory(Shi-Tomasi)
add_subdirectory(Blob)
add_subdirectory(SIFT)

target_link_libraries(MatTraversal ${OpenCV_LIBS})

