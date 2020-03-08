cmake_minimum_required(VERSION 3.16)
project(pyre) 

# Build external dependencies
add_subdirectory(external)

set(PYRE_SRC
    src/Pyre/Application.cpp
    src/Pyre/Log.cpp
    src/Pyre/Renderer/Renderer.cpp
    src/Pyre/Renderer/RenderCommand.cpp
    src/Pyre/Renderer/RenderAPI.cpp
    src/Pyre/Renderer/Shader.cpp
    src/Pyre/Renderer/Buffer.cpp
    src/Pyre/Renderer/VertexArray.cpp
    src/Pyre/Renderer/Camera.cpp
    src/Pyre/Layers/Layer.cpp
    src/Pyre/Layers/LayerStack.cpp
    src/Pyre/Layers/ImGuiLayer.cpp
    src/Platform/OpenGL/OpenGLRenderAPI.cpp
    src/Platform/OpenGL/OpenGLContext.cpp
    src/Platform/OpenGL/OpenGLShader.cpp
    src/Platform/OpenGL/OpenGLBuffer.cpp
    src/Platform/OpenGL/OpenGLVertexArray.cpp
    src/Platform/Windows/WindowsWindow.cpp
    src/Platform/Windows/WindowsInput.cpp
)

set(PYRE_PCH src/pyrepch.hpp)

add_library(pyre STATIC ${PYRE_SRC})
target_precompile_headers(pyre PRIVATE ${PYRE_PCH})

target_link_libraries(pyre
    PRIVATE glfw glad imgui_opengl_glfw
    PUBLIC spdlog imgui glm_static 
)
target_compile_definitions(pyre
    PRIVATE
        -DGLFW_INCLUDE_NONE  # GLFW won't include its own OpenGL
    PUBLIC
        $<$<PLATFORM_ID:Windows>:PYRE_PLATFORM_WINDOWS>
        $<$<PLATFORM_ID:Linux>:PYRE_PLATFORM_LINUX>
)  
target_include_directories(pyre PUBLIC src)

target_compile_options(pyre PUBLIC
    $<$<CONFIG:DEBUG>:   #DEBUG
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
            -Wall -Werror -Wextra -pedantic -O0 -g>
        $<$<CXX_COMPILER_ID:MSVC>:
            /W3 /ZI /RTC1 /sdl /Od>>
    $<$<CONFIG:RELEASE>: #RELEASE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
            -O2 -s -DNDEBUG>
        $<$<CXX_COMPILER_ID:MSVC>:
            /Zi /GL /O2>>
)
target_link_options(pyre PUBLIC
    $<$<CONFIG:RELEASE>:$<$<CXX_COMPILER_ID:MSVC>:
        /LTCG>>
)