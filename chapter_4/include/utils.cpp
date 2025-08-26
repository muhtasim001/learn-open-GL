#include "utils.hpp"
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

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

GLuint utils::createShaderProgram(const char *vp, const char *fp) {
    
    //read in the shaders into strings
    string vertShaderStr = utils::readShaderSource(vp);
    string fragShaderStr = utils::readShaderSource(fp);

    //convert them to c strings
    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *fragShaderSrc = fragShaderStr.c_str();

    //create the shaders
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    //attach the shader shader programs to the shader Gluit objects
    glShaderSource(vShader , 1, &vertShaderSrc, NULL);
    glShaderSource(fShader, 1, &fragShaderSrc, NULL);

    //comple the shader program and do error logging
    glCompileShader(vShader);
    utils::print_shader_error(utils::VERT, vShader);

    glCompileShader(fShader);
    utils::print_shader_error(utils::FRAG, fShader);

    //create the shader program
    GLuint vfprogram = glCreateProgram();
    glAttachShader(vfprogram, vShader);
    glAttachShader(vfprogram, fShader);

    glLinkProgram(vfprogram);
    utils::print_linking_error(vfprogram);

    return vfprogram;

}

GLuint utils::createShaderProgram(const char *vp, const char *gp, const char *fp) {

    //read in the shader into strings
    std::string vertShaderStr = utils::readShaderSource(vp);
    std::string geoShaderStr = utils::readShaderSource(gp);
    std::string fragShaderStr = utils::readShaderSource(fp);

    //convert them to c strings
    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *geoShaderSrc = geoShaderStr.c_str();
    const char *fragShaderSrc = fragShaderStr.c_str();

    //create the shaders
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint gShader = glCreateShader(GL_GEOMETRY_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    //attach the shader src to the shaders objects
    glShaderSource(vShader, 1, &vertShaderSrc, NULL);
    glShaderSource(gShader, 1, &geoShaderSrc, NULL);
    glShaderSource(fShader, 1, &fragShaderSrc, NULL);

    //comple the shader program and do error logging
    glCompileShader(vShader);
    utils::print_shader_error(utils::VERT, vShader);

    glCompileShader(gShader);
    utils::print_shader_error(utils::GEO, gShader);

    glCompileShader(fShader);
    utils::print_shader_error(utils::FRAG, fShader);

    //create the shader program
    GLuint vgfprogram = glCreateProgram();
    glAttachShader(vgfprogram, vShader);
    glAttachShader(vgfprogram, gShader);
    glAttachShader(vgfprogram, fShader);

    glLinkProgram(vgfprogram);
    utils::print_linking_error(vgfprogram);

    return vgfprogram;
}
