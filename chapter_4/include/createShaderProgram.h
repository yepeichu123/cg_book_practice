#ifndef CREATE_SHADER_PROGRAM_H
#define CREATE_SHADER_PROGRAM_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class CreateShaderProgram {
public:
    CreateShaderProgram();

    ~CreateShaderProgram();

    GLuint runCreateShaderProgram(const std::string& vshaderSrcPath, const std::string& fshaderSrcPath);
};

#endif