cmake_minimum_required(VERSION 3.16)
project(pyre) 

add_definitions(-DPYRE_BUILD_LIB)

set(SOURCE_FILES
  src/Pyre/Application.cpp
  src/Pyre/Log.cpp)

set(PCH_FILES src/pyrepch.hpp)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_precompile_headers(${PROJECT_NAME} PRIVATE ${PCH_FILES})