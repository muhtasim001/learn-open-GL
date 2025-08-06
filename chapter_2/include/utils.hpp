#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

namespace utils {
    void printShaderLog(GLuint shader);
    void printProgramLog(int prog);
    bool checkOpenGLError();
    string readShaderSource(const char *filePath);
    void print_shader_error(const char* shader_type, GLuint shader);
    void print_linking_error(int prog);

    inline constexpr const char* VERT = "vertex";
    inline constexpr const char* FRAG = "fragment";
};
