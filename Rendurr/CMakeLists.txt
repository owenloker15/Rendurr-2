cmake_minimum_required(VERSION 4.1)

# Create visual studio project
project(Rendurr)

# Set sources
set(RENDURR_SOURCES
    src/Rendurr.hpp

    src/Core/Application.hpp
    src/Core/Application.cpp
    src/Core/Input.hpp
    src/Core/Layer.hpp
    src/Core/LayerStack.hpp
    src/Core/LayerStack.cpp
    src/Core/Log.hpp
    src/Core/Log.cpp
    src/Core/Window.hpp
    src/Core/Window.cpp

    src/Events/Event.hpp
    src/Events/EventPublisher.hpp
    src/Events/EventPublisher.cpp

    src/Render/IndexBuffer.hpp
    src/Render/IndexBuffer.cpp
    src/Render/RenderContext.hpp
    src/Render/RenderContext.cpp
    src/Render/Renderer.hpp
    src/Render/Renderer.cpp
    src/Render/Shader.hpp
    src/Render/Shader.cpp
    src/Render/ShaderUniforms.hpp
    src/Render/ShaderUniforms.cpp
    src/Render/Texture.hpp
    src/Render/Texture.cpp
    src/Render/VertexArray.hpp
    src/Render/VertexArray.cpp
    src/Render/VertexBuffer.hpp
    src/Render/VertexBuffer.cpp

    src/Scene/Camera.hpp
    src/Scene/Camera.cpp

    src/Utils/FileUtils.hpp
    src/Utils/Timer.hpp
)

# Create static library
add_library(Rendurr STATIC ${RENDURR_SOURCES})

# Group into src directory in visual studio file tree
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "src" FILES ${RENDURR_SOURCES})

# Set include directory as src
target_include_directories(Rendurr PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/ThirdParty/glm
)

# Link publicly (all things liking to this will inherit)
target_link_libraries(Rendurr PUBLIC 
    glad
    glfw
    spdlog
)

target_link_libraries(Rendurr PRIVATE 
    stb_image
)

# Prevents glfw from including any opengl headers
target_compile_definitions(Rendurr PUBLIC GLFW_INCLUDE_NONE)
