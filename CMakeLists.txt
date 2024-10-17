cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(colisions)

add_executable(colisions "src/main.cpp")

include_directories("include")

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(colisions PRIVATE glfw)

find_package(GLEW REQUIRED)
target_link_libraries(colisions PRIVATE GLEW::GLEW)

find_package(OpenGL REQUIRED)
target_link_libraries(colisions PRIVATE OpenGL::GL)

find_package(glm CONFIG REQUIRED)
target_link_libraries(colisions PRIVATE glm::glm)

add_compile_definitions(SHADER_DIR="../shader/")
