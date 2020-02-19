cmake_minimum_required(VERSION 3.16)
project(sandbox)

set(SOURCE_FILES
    src/Sandbox.cpp
)

include_directories(
    ${pyre_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE pyre)