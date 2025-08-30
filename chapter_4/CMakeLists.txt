<<<<<<< HEAD
cmake_minimum_required(VERSION 3.10)
project(chapter_4)

# setting the cpp or c standart being used
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # need this on for clangd

#setting an open gl option
cmake_policy(SET CMP0072 NEW)
set(Open_GL_PREFRENCE GLVND)

#finding open gl and glm packages or any other needed packages
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

#the include directories of things we want in the project
include_directories(
    /usr/local/include/
    ${CMAKE_SOURCE_DIR}/include
)

#location of the librariy files we need
link_directories(/usr/local/lib/)

#add the chapter programs there
add_executable(program_2.5re src/program_2.5re.cpp include/utils.cpp)
target_link_libraries(program_2.5re PRIVATE glfw GLEW glm::glm GL)

#add the chapter programs there
add_executable(program_4.1 src/program_4.1.cpp include/utils.cpp)
target_link_libraries(program_4.1 PRIVATE glfw GLEW glm::glm GL)

#add the chapter programs there
add_executable(program_4.1ani src/program_4.1ani.cpp include/utils.cpp)
target_link_libraries(program_4.1ani PRIVATE glfw GLEW glm::glm GL)

#add the chapter programs there
add_executable(program_4.2 src/program_4.2.cpp include/utils.cpp)
target_link_libraries(program_4.2 PRIVATE glfw GLEW glm::glm GL)

#copy the shaders folder into build, but need to run cmake everytime
file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
