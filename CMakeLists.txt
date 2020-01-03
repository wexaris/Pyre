cmake_minimum_required( VERSION 3.10 )
project(pyre-project)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_STANDARD 17)

# Pass platform specific flags
if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  add_definitions(-DPYRE_PLATFORM_WINDOWS)
elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  add_definitions(-DPYRE_PLATFORM_LINUX)
endif()

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -Wextra -pedantic -O0 -g -DDEBUG")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -O2 -s -DNDEBUG")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W3 /ZI /RTC /sdl /Od")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} /Zi /GL /O2")
endif()

include_directories(
  pyre/src
  ${CMAKE_SOURCE_DIR}/Pyre/external/spdlog/include
)

add_subdirectory(pyre)
add_subdirectory(sandbox)