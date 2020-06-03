#!/bin/sh

## script to cross compile lv_example for the Omega2 using Docker

# make sure the submodules are initialized
git submodule update --init --recursive
if [ -d bin ]; then
  rm -rf bin/*
else
  mkdir bin
fi

# build the image
docker build -t cross_compile .

# run it with bin directory mounted as volume
docker run \
  --name build \
  --rm \
  -v `pwd`/bin:/root/source/bin \
  cross_compile
