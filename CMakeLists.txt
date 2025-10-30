cmake_minimum_required(VERSION 4.1)

project(RendurrProject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add third-party libraries
add_subdirectory(Thirdparty/glad)
add_subdirectory(Thirdparty/glfw)
add_subdirectory(Thirdparty/glm)
add_subdirectory(Thirdparty/spdlog)

add_subdirectory(Rendurr)
add_subdirectory(Editurr)