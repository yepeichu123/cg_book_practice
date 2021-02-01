#include "exceptionCatch.h"
#include <cstdlib>
#include <iostream>

ExceptionCatch::ExceptionCatch() {

}

ExceptionCatch::~ExceptionCatch() {

}

void ExceptionCatch::printShaderLog(GLuint shader) {
    int logLength = 0;
    int chWrittn = 0;
    char *log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 0) {
        log = (char *)malloc(logLength);
        glGetShaderInfoLog(shader, logLength, &chWrittn, log);
        std::cout << "Shader Info Log: " << log << std::endl;
        free(log);
    }
}

void ExceptionCatch::printProgramLog(const int& prog) {
    int logLength = 0;
    int chWrittn = 0;
    char *log;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 0) {
        log = (char *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &chWrittn, log);
        std::cout << "Program Info Log: " << log << std::endl;
        free(log);
    }
}

bool ExceptionCatch::checkOpenGLError() {
    bool foundError = false;
    int glError = glGetError();
    while (glError != GL_NO_ERROR) {
        std::cout << "glError: " << glError << std::endl;
        foundError = true;
        glError = glGetError();
    }
    return foundError;
}