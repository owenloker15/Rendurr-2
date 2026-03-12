cmake_minimum_required(VERSION 4.1)

project(RendurrProject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(THIRDPARTY_DIR ${CMAKE_SOURCE_DIR}/ThirdParty)

# Add third-party libraries
add_subdirectory(ThirdParty/glad)
add_subdirectory(ThirdParty/glfw)
add_subdirectory(ThirdParty/glm)
add_subdirectory(ThirdParty/spdlog)
add_subdirectory(ThirdParty/stb_image)

set_target_properties(glad PROPERTIES FOLDER "ThirdParty")
set_target_properties(glfw PROPERTIES FOLDER "ThirdParty")
set_target_properties(glm PROPERTIES FOLDER "ThirdParty")
set_target_properties(spdlog PROPERTIES FOLDER "ThirdParty")
set_target_properties(stb_image PROPERTIES FOLDER "ThirdParty")

# Add Rendurr libraries
add_subdirectory(Rendurr)
set_target_properties(Rendurr PROPERTIES FOLDER "Rendurr")

# Add Editurr libraries
add_subdirectory(Editurr)
set_target_properties(Editurr PROPERTIES FOLDER "Editurr")
