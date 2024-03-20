cmake_minimum_required (VERSION 3.11)
set (CMAKE_CXX_STANDARD 17)

project(test
  LANGUAGES CXX
  VERSION 1.0.0
)

add_executable(test 
#BEGINLIB
    ${CMAKE_SOURCE_DIR}/src/main.cpp
#ENDLIB
)

target_include_directories(test PRIVATE include)
