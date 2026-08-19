cmake_minimum_required(VERSION 4.1)

# Create visual studio project
project(Rendurr)

# Set sources
set(RENDURR_SOURCES
    src/Rendurr.h
    src/Rendurr.cpp

    src/Core/Input.h
    src/Core/Log.h
    src/Core/Log.cpp
    src/Core/Window.h
    src/Core/Window.cpp

    src/Render/Framebuffer.hpp
    src/Render/Framebuffer.cpp
    src/Render/IndexBuffer.hpp
    src/Render/IndexBuffer.cpp
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

# ImGuizmo
add_library(imguizmo STATIC
    ${THIRDPARTY_DIR}/imguizmo/src/ImGuizmo.cpp
    ${THIRDPARTY_DIR}/imguizmo/src/GraphEditor.cpp
    ${THIRDPARTY_DIR}/imguizmo/src/ImCurveEdit.cpp
    ${THIRDPARTY_DIR}/imguizmo/src/ImGradient.cpp
    ${THIRDPARTY_DIR}/imguizmo/src/ImSequencer.cpp
    ${THIRDPARTY_DIR}/imguizmo/src/ImVectorEditor.cpp
)

# Set ImGuizmo public include directories
target_include_directories(imguizmo PUBLIC
    ${THIRDPARTY_DIR}/imguizmo/src
)

# Link ImGuizmo to libraries
target_link_libraries(imguizmo PUBLIC
    imgui
)

# Add ImGuizmo to ThirdParty folder in Visual Studio
set_target_properties(imguizmo PROPERTIES FOLDER "ThirdParty")

# Link publicly (all things linking to this will inherit)
target_link_libraries(Rendurr PUBLIC 
    imgui
    imguizmo
)

target_link_libraries(Rendurr PRIVATE 
    glad
    stb_image
    spdlog
    glfw
)

# Compile Defs

# Prevents glfw from including any opengl headers
target_compile_definitions(Rendurr PUBLIC GLFW_INCLUDE_NONE)

target_compile_definitions(Rendurr
    PRIVATE
        $<$<CONFIG:Debug>:RND_ENABLE_ASSERTS>
)
