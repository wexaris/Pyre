cmake_minimum_required(VERSION 3.16)
project(pyre) 

# Build external dependencies
add_subdirectory(external)

# PYRE_BUILD_LIB     set API macro to export
# GLFW_INCLUDE_NONE  pervent GLFW form including its own OpenGL headers
add_definitions(-DPYRE_BUILD_LIB -DGLFW_INCLUDE_NONE)

set(SOURCE_FILES
    src/Pyre/Application.cpp
    src/Pyre/Log.cpp
    src/Pyre/Windows/WindowsWindow.cpp
    src/Pyre/Layers/Layer.cpp
    src/Pyre/Layers/LayerStack.cpp
    src/Pyre/Layers/ImGuiLayer.cpp
    src/Pyre/Layers/ImGuiRenderer.cpp
    src/Pyre/Input/WindowsInput.cpp
)

set(PCH_FILES src/pyrepch.hpp)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_precompile_headers(${PROJECT_NAME} PRIVATE ${PCH_FILES})

target_link_libraries(${PROJECT_NAME}
    PUBLIC spdlog glm
    PRIVATE glfw glad imgui
)
target_include_directories(${PROJECT_NAME}
    PUBLIC src ${spdlog_INCLUDE_DIRS} ${glm_INCLUDE_DIRS}
    PRIVATE ${glfw_INCLUDE_DIRS} ${GLAD_INCLUDE_DIRS} ${imgui_INCLUDE_DIRS} 
)