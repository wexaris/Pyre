cmake_minimum_required(VERSION 3.0)
project(external)

# spdlog
set(SPDLOG_INSTALL CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_BENCH CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_TESTS CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_EXAMPLE CACHE BOOL "" FORCE)

# GLFW
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Glad
set(GLAD_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(spdlog)
add_subdirectory(glfw)
add_subdirectory(glad)
include(imgui.cmake)