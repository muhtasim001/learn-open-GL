cmake_minimum_required(VERSION 3.10)
project(chapter_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_policy(SET CMP0072 NEW)
set(Open_GL_PREFRENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

include_directories(
    /usr/local/include/
    ${CMAKE_SOURCE_DIR}/include
)
link_directories(/usr/local/lib/)

#add the chapter programs there
add_executable(program_2.1 src/program_2.1.cpp)
target_link_libraries(program_2.1 PRIVATE glfw GLEW glm::glm GL)

#add the chapter programs there
add_executable(program_2.2 src/program_2.2.cpp include/utils.cpp)
target_link_libraries(program_2.2 PRIVATE glfw GLEW glm::glm GL)

#add the chapter programs there
add_executable(program_2.4 src/program_2.4.cpp include/utils.cpp)
target_link_libraries(program_2.4 PRIVATE glfw GLEW glm::glm GL)

#add the chapter programs there
add_executable(program_2.5 src/program_2.5.cpp include/utils.cpp)
target_link_libraries(program_2.5 PRIVATE glfw GLEW glm::glm GL)

#add the chapter programs there
add_executable(program_2.6 src/program_2.6.cpp include/utils.cpp)
target_link_libraries(program_2.6 PRIVATE glfw GLEW glm::glm GL)

#copy the shaders folder into build, but need to run cmake everytime
file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
