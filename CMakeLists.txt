cmake_minimum_required(VERSION 2.8)

project(image_viewer)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)

set(SRC_LIST 
src/main.cpp
src/image_viewer.cpp
src/image_viewer.hpp)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
  set(BUILD_DIR build_debug)
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "RELEASE")
  set(BUILD_DIR build_release)
endif()

set(OpenCV_DIR ${CMAKE_CURRENT_BINARY_DIR}/../opencv/build)

find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} ${SRC_LIST})

include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Qt5 COMPONENTS Core Gui Widgets Test Concurrent REQUIRED)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets ${OpenCV_LIBS})





