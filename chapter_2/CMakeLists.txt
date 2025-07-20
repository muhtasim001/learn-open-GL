cmake_minimum_required(VERSION 3.10)
project(chapter_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

cmake_policy(SET CMP0072 NEW)
set(Open_GL_PREFRENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

include_directories(/usr/local/include/)
link_directories(/usr/local/lib/)

#add the chapter programs there
add_executable(program_2.1 src/program_2.1.cpp)
target_link_libraries(program_2.1 PRIVATE glfw GLEW glm::glm GL)
