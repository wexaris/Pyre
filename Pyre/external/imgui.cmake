cmake_minimum_required(VERSION 3.0)
project(imgui)

set(IMGUI_SRC_FILES
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_demo.cpp
)

add_library(imgui STATIC ${IMGUI_SRC_FILES})
target_include_directories(imgui PUBLIC imgui)