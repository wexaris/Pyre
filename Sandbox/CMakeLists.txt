cmake_minimum_required(VERSION 3.10)
project(sandbox)

set(SOURCE_FILES
  src/Sandbox.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} pyre)