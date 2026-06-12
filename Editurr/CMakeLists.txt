cmake_minimum_required(VERSION 4.1)

project(Editurr)

# Asset paths
set(EDITURR_ASSETS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")

# Fill in config file with variables
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/src/EditurrConfig.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/generated/EditurrConfig.h"
)

# Add sources
set(EDITURR_SOURCES
    src/Editurr.h
    src/EditurrEntry.cpp
    src/EditurrLayer.hpp
    src/EditurrLayer.cpp
    src/EditurrUtils.hpp
    src/EditurrUtils.cpp

    src/Render/EditurrRender.h
    src/Render/EditurrRender.cpp

    src/Scene/AssetManager.h
    src/Scene/AssetManager.cpp
    src/Scene/ComponentPool.h
    src/Scene/ComponentPool.cpp
    src/Scene/Components.h
    src/Scene/ECSManager.h
    src/Scene/ECSManager.cpp
    src/Scene/Entity.h
    src/Scene/IComponentPool.h
    src/Scene/Material.h
    src/Scene/Material.cpp
    src/Scene/Mesh.h
    src/Scene/Mesh.cpp
    src/Scene/Model.h
    src/Scene/Model.cpp
    src/Scene/Scene.h
    src/Scene/Scene.cpp
    src/Scene/Texture.h
    src/Scene/Texture.cpp

    src/UI/EditurrUI.h
    src/UI/EditurrUI.cpp
    src/UI/EntityUI.cpp
    src/UI/EntityUI.cpp
    src/UI/ToolbarUI.h
    src/UI/ToolbarUI.cpp
    src/UI/UI.h
    src/UI/UI.cpp
    src/UI/ViewportUI.h
    src/UI/ViewportUI.cpp
)

# Create executable
add_executable(Editurr ${EDITURR_SOURCES})

# Group into src directory in visual studio file tree
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "src" FILES ${EDITURR_SOURCES})

# Include the generated config header
target_include_directories(Editurr PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/generated")

add_custom_command(TARGET Editurr POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:Editurr>/assets"
)

# Link libraries
target_link_libraries(Editurr PRIVATE Rendurr assimp)
