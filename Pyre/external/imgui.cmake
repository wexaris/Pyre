cmake_minimum_required(VERSION 3.10)
project(imgui)

# # # # # # # # # # # # # # # # # # # #
#             Base ImGui              #
# # # # # # # # # # # # # # # # # # # #
file(GLOB IMGUI_SRC_FILES imgui/*.cpp)

add_library(imgui STATIC ${IMGUI_SRC_FILES})
target_include_directories(imgui PRIVATE imgui INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


# # # # # # # # # # # # # # # # # # # #
#    Base OpenGL/GLFW example impl    #
# # # # # # # # # # # # # # # # # # # #
set(IMGUI_OPENGL_GLFW_SRC_FILES
    imgui/examples/imgui_impl_opengl3.cpp
    imgui/examples/imgui_impl_glfw.cpp
)

add_library(imgui_opengl_glfw STATIC ${IMGUI_OPENGL_GLFW_SRC_FILES})
target_link_libraries(imgui_opengl_glfw PRIVATE glfw glad)
target_include_directories(imgui_opengl_glfw PRIVATE imgui ${glfw_INCLUDE_DIRS} ${GLAD_INCLUDE_DIRS})
target_compile_definitions(imgui_opengl_glfw PRIVATE -DIMGUI_IMPL_OPENGL_LOADER_GLAD)