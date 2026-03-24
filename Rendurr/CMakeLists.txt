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

    src/Render/Framebuffer.hpp
    src/Render/Framebuffer.cpp
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
    src/Scene/CameraController.hpp
    src/Scene/CameraController.cpp
    src/Scene/Components.hpp
    src/Scene/ComponentPool.hpp
    src/Scene/ECSManager.hpp
    src/Scene/ECSManager.cpp
    src/Scene/Entity.hpp
    src/Scene/Entity.cpp
    src/Scene/IProjectionStrategy.hpp
    src/Scene/Material.hpp
    src/Scene/Material.cpp
    src/Scene/Mesh.hpp
    src/Scene/Mesh.cpp
    src/Scene/OrthographicProjectionStrategy.hpp
    src/Scene/OrthographicProjectionStrategy.cpp
    src/Scene/Scene.hpp
    src/Scene/Scene.cpp

    src/UI/UiLayer.hpp
    src/UI/UiLayer.cpp

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
    ${THIRDPARTY_DIR}/glm
)

# ImGui
# ImGui sources
set(IMGUI_SOURCES
    ${THIRDPARTY_DIR}/imgui/imgui.cpp
    ${THIRDPARTY_DIR}/imgui/imgui_demo.cpp
    ${THIRDPARTY_DIR}/imgui/imgui_draw.cpp
    ${THIRDPARTY_DIR}/imgui/imgui_tables.cpp
    ${THIRDPARTY_DIR}/imgui/imgui_widgets.cpp
    ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

# Add ImGui
add_library(imgui STATIC ${IMGUI_SOURCES})

# Set ImGui public include directories
target_include_directories(imgui PUBLIC
    ${THIRDPARTY_DIR}/imgui
    ${THIRDPARTY_DIR}/imgui/backends
)

# Link ImGui to libraries
target_link_libraries(imgui PUBLIC 
    glfw
) 
# Add ImGui to ThirdParty folder in Visual Studio
set_target_properties(imgui PROPERTIES FOLDER "ThirdParty")

# Link publicly (all things liking to this will inherit)
target_link_libraries(Rendurr PUBLIC 
    glad
    glfw
    spdlog
    imgui
)

target_link_libraries(Rendurr PRIVATE 
    stb_image
)

# Compile Defs

# Prevents glfw from including any opengl headers
target_compile_definitions(Rendurr PUBLIC GLFW_INCLUDE_NONE)

target_compile_definitions(Rendurr
    PRIVATE
        $<$<CONFIG:Debug>:RND_ENABLE_ASSERTS>
)
