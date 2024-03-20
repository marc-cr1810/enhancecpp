#!/bin/bash

SRC_FILES="$(for SRC_FILE in $(find src -type f -name "*.cpp" | sort); do echo -n "    "'${CMAKE_SOURCE_DIR}'"/$SRC_FILE\n"; done)"
sed -i CMakeLists.txt -e "/#BEGINLIB/,/#ENDLIB/c\#BEGINLIB\n$SRC_FILES#ENDLIB"