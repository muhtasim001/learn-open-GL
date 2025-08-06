#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>
#include "utils.hpp"

#define numVAOs 1

using namespace std;

GLuint renderingProgram;
GLuint vao[numVAOs];

GLuint createShaderProgram() {
    string vertShaderStr = utils::readShaderSource("shaders/vShader2.5.glsl");
    string fragShaderStr = utils::readShaderSource("shaders/fShader2.5.glsl");

    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *fragShaderSrc = fragShaderStr.c_str();

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vertShaderSrc, NULL);
    glShaderSource(fShader, 1, &fragShaderSrc, NULL);

    glCompileShader(vShader);
    utils::print_shader_error(utils::VERT, vShader);

    glCompileShader(fShader);
    utils::print_shader_error(utils::FRAG, fShader);

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);

    glLinkProgram(vfProgram);
    utils::print_linking_error(vfProgram);

    return vfProgram;
}

void init (GLFWwindow * window) {
    renderingProgram = createShaderProgram();
    glGenVertexArrays(numVAOs,vao);
    glBindVertexArray(vao[0]);
}

void display (GLFWwindow * window, double current_time) {
    glUseProgram(renderingProgram);
    //glPointSize(30.0f);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main (void) {
    if (!glfwInit()) {
        cout << "failed to init glfw \n";
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow * window = glfwCreateWindow(600, 600, "program 2.5", NULL, NULL);
    glfwMakeContextCurrent(window);

    //don't use conditonal to instalize glew, fails on wayland
    glewInit();

    glfwSwapInterval(1);
    init(window);

    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

}
