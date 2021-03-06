
set(PROJ spdlog)

# spdlog uses a debug suffix
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(dsuffix "d")
endif()

set(LIB_DIR ${CMAKE_BINARY_DIR}/lib)
set(LIB_NAME ${prefix}${PROJ}${dsuffix}${suffix})

ExternalProject_Add(${PROJ}_proj
    PREFIX     "${CMAKE_CURRENT_BINARY_DIR}/${PROJ}"
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${PROJ}"
    CMAKE_ARGS
        -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
        -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        -DCMAKE_LIBRARY_OUTPUT_DIRECTORY=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
        -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/${PROJ}
    CMAKE_CACHE_ARGS
        -DSPDLOG_INSTALL:BOOL=OFF
        -DSPDLOG_BUILD_BENCH:BOOL=OFF
        -DSPDLOG_BUILD_TESTS:BOOL=OFF
        -DSPDLOG_BUILD_EXAMPLE:BOOL=OFF
    INSTALL_COMMAND ""
    BUILD_BYPRODUCTS ${LIB_DIR}/${LIB_NAME}
)

set(INCL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${PROJ}/include)

add_library(${PROJ} STATIC IMPORTED GLOBAL)
add_dependencies(${PROJ} ${PROJ}_proj)
set_target_properties(${PROJ} PROPERTIES
    IMPORTED_LOCATION ${LIB_DIR}/${LIB_NAME}
    INTERFACE_INCLUDE_DIRECTORIES ${INCL_DIR}
)