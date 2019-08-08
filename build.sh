#!/bin/bash

function build {
  mkdir $1
  cd $1
  cmake -DCMAKE_BUILD_TYPE=$2 ../
  make
  cd ..
}

build build_debug DEBUG
build build_release RELEASE

