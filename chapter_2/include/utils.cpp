#include "utils.hpp"
#include <cstdlib>
#include <fstream>
#include <string>

bool utils::checkOpenGLError() {

    bool foundError = false;
    int glErr = glGetError();
    
    while (glErr != GL_NO_ERROR) {
        cout << "glError:" << glErr << endl;
        foundError = true;
        glErr = glGetError();
    }

    return foundError;
}

void utils::printProgramLog(int prog) {

    int len = 0;
    int chWrittn = 0;
    char *log;

    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = (char *)malloc(len);
        glGetProgramInfoLog(prog, len, &chWrittn, log);
        cout << "Program Info Log: " << endl;
        free(log);
    }
}

void utils::printShaderLog(GLuint shader) {

    int len = 0;
    int chWrittn = 0;
    char *log;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = (char *)malloc(len);
        glGetShaderInfoLog(shader, len, &chWrittn, log);
        cout << "Shader info Log: " << log << endl;
        free(log);
    }

}

void utils::print_shader_error(const char* shader_type, GLuint shader) {

    GLint shader_compiled;

    utils::checkOpenGLError();
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compiled);
    if (shader_compiled != GL_TRUE) {
        cout << shader_type << " shader compilation failed" << endl;
        utils::printShaderLog(shader);
    }
}

void utils::print_linking_error(int prog) {
    
    GLint linked;
    utils::checkOpenGLError();

    glGetProgramiv(prog, GL_LINK_STATUS, &linked);
    if (linked != GL_TRUE) {
        cout << "linking has failed" << endl;
        utils::printProgramLog(prog);
    }
}

string utils::readShaderSource(const char *filePath) {

    string content;
    ifstream fileStream(filePath, ios::in);

    //error checking for files
    if (!fileStream.is_open()) {
        cout << "file not found or path is not correct" << endl;
    }

    string line = "";

    while (!fileStream.eof()) {
        getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}
