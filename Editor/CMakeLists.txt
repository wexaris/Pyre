cmake_minimum_required(VERSION 3.16)
project(editor)

set(SOURCE_FILES
    src/Editor.cpp
    src/EditorLayer.cpp
)

add_executable(editor WIN32 ${SOURCE_FILES})
add_dependencies(editor pyre)

target_link_libraries(editor PRIVATE pyre)