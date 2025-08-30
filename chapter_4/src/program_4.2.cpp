#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "utils.hpp"

using namespace std;

#define numVAOs 1
#define numVBOs 2

float camX, camY, camZ;
float cubeLocX, cubeLocY, cubeLocZ;

GLuint renderingProgram;
GLuint vao[numVAOs];

GLuint bao[numVAOs];
GLuint vbo[numVBOs];

//allocate variables used in display function, so they 
//don't need to be allocatted during rendering
GLuint pLoc, vLoc, tfLoc;
int width, hight;
float aspect;
glm::mat4 pMat, vMat;

//hard code the vertecies for the cube
void setupVert (void) {

    float vertexPosition[108] = {
        -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f
    };

    glGenVertexArrays(numVAOs,vao); // generate vao
    glBindVertexArray(vao[0]); // activate vao

    glGenBuffers(numVBOs, vbo); // generate vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // activate vbo
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPosition), vertexPosition, GL_STATIC_DRAW); // put data into buffer

}

//the initilization funtion, that settings all starting values
void init (GLFWwindow * window) {

    // the shader file paths
    const char *vShaderSrc = "shaders/vShader4.2.glsl";
    const char *fShaderSrc = "shaders/fShader4.1.glsl";

    //attaching the shaders to our rendering program
    renderingProgram = utils::createShaderProgram(vShaderSrc, fShaderSrc);

    camX = 0.0f; camY = 0.0f; camZ = 800.0f;
    cubeLocX = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f; //shift down the y 

    //build the prespective matrix
    glfwGetFramebufferSize(window, &width, &hight);
    aspect = (float)width / (float)hight;
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

    setupVert();

}

//the main rendering loop, the stuff that gets update every frame
void display (GLFWwindow * window, double current_time) {
    
    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);

    //get the location of unifrom vars
    vLoc = glGetUniformLocation(renderingProgram, "v_matrix");
    pLoc = glGetUniformLocation(renderingProgram, "p_matrix");
    tfLoc = glGetUniformLocation(renderingProgram, "tf");

    //build the view matrix, coule be static for this case, but need to be rebuild it 
    //the camera could move around
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-camX, -camY, -camZ));

    //send the unifrom variables over
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat));
    glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(pMat));

    float timeFactor = static_cast<float>(current_time);
    glUniform1f(tfLoc, timeFactor);

    //accociate the VBO with the vertex atribute in the shader
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    //adjust openGl settings and draw the model
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 100000);

}

int main (void) {

    if (!glfwInit()) {
        cout << "failed to init glfw \n";
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow * window = glfwCreateWindow(1280, 720, "program_4.2 100,000 cubes", NULL, NULL);
    glfwMakeContextCurrent(window);

    //don't use conditonal to instalize glew, fails on wayland
    glewInit();

    glfwSwapInterval(1);
    init(window);

    // the game / graphics loop
    while (!glfwWindowShouldClose(window)) {

        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

}
