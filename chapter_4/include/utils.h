#ifndef UTILS_H
#define UTILS_H

#include "exceptionCatch.h"
#include "readShaderSource.h"
#include "saveImage.h"
#include "createShaderProgram.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>

// combining all the tools
class Utils {
public:
    // consruct all pointers to use those functions
    Utils();

    ~Utils();

    // exception catch
    // ...
    void printShaderLog(GLuint shader);

    void printProgramLog(const int& prog);

    bool checkOpenGLError();

    // read shader source from files
    // ...
    std::string runReadShaderSource(const std::string& filePath);    

    // save image as types of opencv
    // ...
    void runSaveImage(std::string& outputPath);

    // create shader program
    // ...
    GLuint runCreateShaderProgram(const std::string& vshaderSrcPath, const std::string& fshaderSrcPath);

private:
    // exception catch pointer
    std::shared_ptr<ExceptionCatch> mpExpCatch_;

    // read shader source pointer
    std::shared_ptr<ReadShaderSource> mpReadShaScr_;

    // save image pointer
    std::shared_ptr<SaveImage> mpSaveImage_;

    // create shader program pointer
    std::shared_ptr<CreateShaderProgram> mpCreateShaProg_;
};

#endif