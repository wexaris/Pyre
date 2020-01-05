cmake_minimum_required(VERSION 3.16)
project(pyre) 

add_definitions(-DPYRE_BUILD_LIB -DGLFW_INCLUDE_NONE)

set(SOURCE_FILES
    src/Pyre/Application.cpp
    src/Pyre/Log.cpp
    src/Pyre/Windows/WindowsWindow.cpp
    src/Pyre/Layers/Layer.cpp
    src/Pyre/Layers/LayerStack.cpp
)

set(PCH_FILES src/pyrepch.hpp)

include_directories(
    ${glfw_INCLUDE_DIRS}
    ${GLAD_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_precompile_headers(${PROJECT_NAME} PRIVATE ${PCH_FILES})
target_link_libraries(${PROJECT_NAME} glfw glad)