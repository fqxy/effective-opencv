cmake_minimum_required(VERSION 2.8)

project(effective-opencv)

set(OpenCV_DIR "usr/local/opencv331/share/OpenCV")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(MatTraversal MatTraversal.cpp)

target_link_libraries(MatTraversal ${OpenCV_LIBS})

