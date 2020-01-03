cmake_minimum_required(VERSION 3.10)
project(pyre) 

add_definitions(-DPYRE_BUILD_LIB)

set(SOURCE_FILES
  src/Pyre/Application.cpp
  src/Pyre/Log.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})