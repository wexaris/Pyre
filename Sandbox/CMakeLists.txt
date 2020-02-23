cmake_minimum_required(VERSION 3.16)
project(sandbox)

set(SOURCE_FILES
    src/Sandbox.cpp
)

add_executable(sandbox ${SOURCE_FILES})
add_dependencies(sandbox pyre)

target_link_libraries(sandbox PRIVATE pyre)