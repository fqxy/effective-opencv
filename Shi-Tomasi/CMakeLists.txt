add_executable(goodFeaturesToTrack goodFeaturesToTrack.cpp)
add_executable(thresh thresh.cpp)

target_link_libraries(goodFeaturesToTrack ${OpenCV_LIBS})
target_link_libraries(thresh ${OpenCV_LIBS})
