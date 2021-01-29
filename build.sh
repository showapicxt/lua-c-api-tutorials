#!/bin/bash
SOURCE_DIR=`pwd`
cmake -D CMAKE_INSTALL_PREFIX=.  $SOURCE_DIR  && make && make install

