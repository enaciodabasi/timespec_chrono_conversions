#!/usr/bin/env bash

set -Eeuo pipefail

current_user="naci"

if [ -z {current_user+x}]; then
  return 1
fi

project_dir=/home/${current_user}/timespec_chrono_conversions

if [ ! -d ${project_dir}/build ]; then
  mkdir -p ${project_dir}/build
fi

cd ${project_dir}/build
cmake ..
cmake --build . --target install