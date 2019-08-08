cmake_minimum_required(VERSION 2.8)

project(image_viewer)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)

set(SRC_LIST 
src/main.cpp
src/image_viewer.cpp
src/image_viewer.hpp)

set(BUILD_DIR build_debug)

if (CMAKE_BUILD_TYPE STREQUAL "DEBUG")
  set(BUILD_DIR build_debug)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "RELEASE")
  set(BUILD_DIR build_release)
endif()

set(OPENCV_DIR ${CMAKE_CURRENT_BINARY_DIR}/../opencv/${BUILD_DIR})

include_directories(${OPENCV_DIR}/install/include/opencv4/)

add_executable(${PROJECT_NAME} ${SRC_LIST})

set(OPENCV_LIBS
-lopencv_imgcodecs
-lopencv_imgproc
-lopencv_core
-lopencv_highgui
-lade
-lippiw
-llibjpeg-turbo
-lIlmImf
-littnotify
-llibpng
-llibwebp
-lippicv
-llibjasper
-llibprotobuf
-lquirc
-pthread
-ldl
-lzlib
-llibtiff)

target_link_libraries(${PROJECT_NAME} -L${OPENCV_DIR}/install/lib/)
target_link_libraries(${PROJECT_NAME} -L${OPENCV_DIR}/install/lib/opencv4/3rdparty/)
target_link_libraries(${PROJECT_NAME} ${OPENCV_LIBS})
target_link_libraries(${PROJECT_NAME} ${GTK_LIBRARIES})


