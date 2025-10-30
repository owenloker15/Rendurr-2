cmake_minimum_required(VERSION 4.1)

project(Editurr)

# Add sources
set(EDITURR_SOURCES
    src/Editurr.cpp
    src/EditurrLayer.hpp
    src/EditurrLayer.cpp
)

# Create executable
add_executable(Editurr ${EDITURR_SOURCES})

# Group into src directory in visual studio file tree
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "src" FILES ${EDITURR_SOURCES})

add_custom_command(TARGET Editurr POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)

# Link libraries
target_link_libraries(Editurr PRIVATE Rendurr)