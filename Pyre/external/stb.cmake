cmake_minimum_required(VERSION 3.10)
project(stb)

# # # # # # # # # # # # # # # # # # # #
#             Base ImGui              #
# # # # # # # # # # # # # # # # # # # #
file(GLOB STB_SRC_FILES stb/stb_image.cpp)

add_library(stb STATIC ${STB_SRC_FILES})
target_include_directories(stb INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})