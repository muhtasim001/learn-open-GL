#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


using namespace std;

void init (GLFWwindow * window) {

}

void display (GLFWwindow * window, double current_time) {
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main (void) {
    if (!glfwInit()) {
        cout << "failed to init glfw \n";
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow * window = glfwCreateWindow(600, 600, "program 2.1", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        cout << "failed to initalize glew \n";
        exit(EXIT_FAILURE);
    }

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


