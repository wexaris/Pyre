cmake_minimum_required(VERSION 3.16)
project(pyre-project)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_STANDARD 17)

# pervent override warnings
string(REPLACE "/Zi" "/ZI" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})

add_subdirectory(Pyre)
add_subdirectory(Sandbox)