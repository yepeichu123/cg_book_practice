#include "createShaderProgram.h"
#include "readShaderSource.h"
#include <memory>

CreateShaderProgram::CreateShaderProgram() {

}

CreateShaderProgram::~CreateShaderProgram() {

}

GLuint CreateShaderProgram::runCreateShaderProgram(
    const std::string& vshaderSrcPath, const std::string& fshaderSrcPath) {
    std::shared_ptr<ReadShaderSource> pReadShaderSource = std::make_shared<ReadShaderSource>();
    std::string vshaderSource = pReadShaderSource->runReadShaderSource(vshaderSrcPath);
    std::string fshaderSource = pReadShaderSource->runReadShaderSource(fshaderSrcPath);
    const char *vshaderSourceSrc = vshaderSource.c_str();
    const char *fshaderSourceSrc = fshaderSource.c_str();

    // create the vertex shader and fragment shader
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    // load the char into two shaders and compile
    glShaderSource(vShader, 1, &vshaderSourceSrc, NULL);
    glShaderSource(fShader, 1, &fshaderSourceSrc, NULL);

    // catch compiling error
    glCompileShader(vShader);
    glCompileShader(fShader);

    // create the shader program
    GLuint vfProgram = glCreateProgram();

    // load two shaders into program
    // catch linking error
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);

    return vfProgram;
}