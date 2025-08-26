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
    GLuint createShaderProgram(const char *vp, const char *fp);
    GLuint createShaderProgram(const char *vp, const char *gp, const char *fp);
    GLuint createShaderProgram(const char *vp, const char *tCS, const char *tES, const char *fp);
    GLuint createShaderProgram(const char *vp, const char *tCS, const char *tES, const char *gp, const char *fp);

    inline constexpr const char* VERT = "vertex";
    inline constexpr const char* FRAG = "fragment";
    inline constexpr const char* GEO = "geometry";
};
