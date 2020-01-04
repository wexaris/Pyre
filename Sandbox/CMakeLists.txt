cmake_minimum_required(VERSION 3.16)
project(sandbox)

set(SOURCE_FILES
  src/Sandbox.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} pyre)