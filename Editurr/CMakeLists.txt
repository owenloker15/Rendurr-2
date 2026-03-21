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
    src/Editurr.hpp
    src/Editurr.cpp
    src/EditurrEntry.cpp
    src/EditurrLayer.hpp
    src/EditurrLayer.cpp
    src/EditurrUtils.hpp
    src/EditurrUtils.cpp
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
target_link_libraries(Editurr PRIVATE Rendurr)