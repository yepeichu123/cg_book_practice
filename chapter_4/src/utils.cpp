#include "utils.h"

// consruct all pointers to use those functions
Utils::Utils() {
    mpExpCatch_ = std::make_shared<ExceptionCatch>();
    mpReadShaScr_ = std::make_shared<ReadShaderSource>();
    mpSaveImage_ = std::make_shared<SaveImage>();
    mpCreateShaProg_ = std::make_shared<CreateShaderProgram>();
}

Utils::~Utils() {

}

// exception catch
// ...
void Utils::printShaderLog(GLuint shader) {
    mpExpCatch_->printShaderLog(shader);
}

void Utils::printProgramLog(const int& prog) {
    mpExpCatch_->printProgramLog(prog);
}

bool Utils::checkOpenGLError() {
    bool foundError = mpExpCatch_->checkOpenGLError();
    return foundError;
}

// read shader source from files
// ...
std::string Utils::runReadShaderSource(const std::string& filePath) {
    std::string shaderSource = mpReadShaScr_->runReadShaderSource(filePath);
    return shaderSource;
}

// save image as types of opencv
// ...
void Utils::runSaveImage(std::string& outputPath) {
    mpSaveImage_->runSaveImage(outputPath);
}

// create shader program
// ...
GLuint Utils::runCreateShaderProgram(
    const std::string& vshaderSrcPath, const std::string& fshaderSrcPath) {
    GLuint vfProgram = mpCreateShaProg_->runCreateShaderProgram(vshaderSrcPath, fshaderSrcPath);
    return vfProgram;
}