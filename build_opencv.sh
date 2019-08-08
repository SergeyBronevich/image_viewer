#!/bin/bash

sudo apt-get install libgtk2.0-dev

cd opencv

function build {
  mkdir $1
  cd $1
  cmake CMAKE_BUILD_TYPE=$2 \
  -D CMAKE_INSTALL_PREFIX=./install \
  -D BUILD_SHARED_LIBS=OFF \
  -D WITH_CUDA=OFF \
  -D BUILD_JAVA=OFF \
  -D BUILD_PERF_TESTS=OFF \
  -D BUILD_TESTS=OFF \
  -D BUILD_PACKAGE=OFF \
  -D BUILD_EXAMPLES=OFF \
  -D BUILD_OPENCV_JAVA_BINDINGS_GENERATOR=OFF \
  -D BUILD_OPENCV_PYTHON_BINDINGS_GENERATOR=OFF \
  -D BUILD_OPENCV_APPS=OFF \
  -D BUILD_opencv_calib3d=OFF \
  -D BUILD_opencv_dnn=OFF \
  -D BUILD_opencv_features2d=OFF \
  -D BUILD_opencv_flann=OFF \
  -D BUILD_opencv_gapi=OFF \
  -D BUILD_opencv_ml=OFF \
  -D BUILD_opencv_objdetect=OFF \
  -D BUILD_opencv_photo=OFF \
  -D BUILD_opencv_stitching=OFF \
  -D BUILD_opencv_video=OFF \
  -D BUILD_opencv_videoio=OFF \
  -D WITH_GTK=ON \
  -D BUILD_PNG=ON \
  -D BUILD_ZLIB=ON \
  ../

  make install

  cd ..
}

build build_debug DEBUG
build build_release RELEASE
