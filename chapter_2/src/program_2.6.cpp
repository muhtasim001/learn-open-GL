#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "utils.hpp"

#define numVAOs 1

using namespace std;

GLuint renderingProgram;
GLuint vao[numVAOs];

float x = 0.0f;
float inc = 0.01f;
double last_time = 0.0;

GLuint createShaderProgram() {
    string vertShaderStr = utils::readShaderSource("shaders/vShader2.6.glsl");

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
    //screen managment
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);

    //glPointSize(30.0f);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (abs(current_time - last_time) >= 0.016) {
        x+= inc;
        last_time = current_time;
    }
    if (x > 1.0)
        inc = -0.01f;
    if (x < -1.0f)
        inc = 0.01f;

    GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset"); // get the ptr to "offset"
    glProgramUniform1f(renderingProgram, offsetLoc, x); // sends value in "x" to "offset"

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
