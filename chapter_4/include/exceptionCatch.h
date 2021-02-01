#ifndef EXCEPTION_CATCH_H
#define EXCEPTION_CATCH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
// #include <GL/gl_mangle.h>

class ExceptionCatch {
public:
    ExceptionCatch();

    ~ExceptionCatch();

    void printShaderLog(GLuint shader);

    void printProgramLog(const int& prog);

    bool checkOpenGLError();
};

#endif 