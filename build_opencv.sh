#!/bin/bash

sudo apt-get install libgtk2.0-dev

cd opencv

function build {
  mkdir $1
  cd $1
  cmake CMAKE_BUILD_TYPE=$2 \
  -DCMAKE_INSTALL_PREFIX=./install \
  -DBUILD_SHARED_LIBS=OFF \
  -DWITH_CUDA=OFF \
  -DBUILD_JAVA=OFF \
  -DBUILD_PERF_TESTS=OFF \
  -DBUILD_TESTS=OFF \
  -DBUILD_PACKAGE=OFF \
  -DBUILD_EXAMPLES=OFF \
  -DBUILD_OPENCV_JAVA_BINDINGS_GENERATOR=OFF \
  -DBUILD_OPENCV_PYTHON_BINDINGS_GENERATOR=OFF \
  -DWITH_GTK=ON \
  ../

  make install

  cd ..
}

build build_debug DEBUG
build build_release RELEASE

