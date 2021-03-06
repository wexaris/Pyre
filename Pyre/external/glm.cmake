
set(PROJ glm)

set(LIB_DIR ${CMAKE_BINARY_DIR}/lib)
set(LIB_NAME ${prefix}${PROJ}_static${suffix})

ExternalProject_Add(${PROJ}_proj
    PREFIX      "${CMAKE_CURRENT_BINARY_DIR}/${PROJ}"
    SOURCE_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/${PROJ}"
    CMAKE_ARGS
        -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
        -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        -DCMAKE_LIBRARY_OUTPUT_DIRECTORY=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
        -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/${PROJ}
    CMAKE_CACHE_ARGS
        -DBUILD_STATIC_LIBS:BOOL=ON
        -DBUILD_SHARED_LIBS:BOOL=OFF
        -DGLM_TEST_ENABLE:BOOL=OFF
    INSTALL_COMMAND ""
    BUILD_BYPRODUCTS ${LIB_DIR}/${LIB_NAME}
)

set(INCL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${PROJ})

add_library(${PROJ}_static STATIC IMPORTED GLOBAL)
add_dependencies(${PROJ}_static ${PROJ}_proj)
set_target_properties(${PROJ}_static PROPERTIES
    IMPORTED_LOCATION ${LIB_DIR}/${LIB_NAME}
    INTERFACE_INCLUDE_DIRECTORIES ${INCL_DIR}
)