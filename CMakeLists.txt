cmake_minimum_required(VERSION 4.1)

project(RendurrProject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add third-party libraries
add_subdirectory(ThirdParty/glad)
add_subdirectory(ThirdParty/glfw)
add_subdirectory(ThirdParty/glm)
add_subdirectory(ThirdParty/spdlog)
add_subdirectory(ThirdParty/stb_image)

# Add Rendurr and Editurr libraries
add_subdirectory(Rendurr)
add_subdirectory(Editurr)
