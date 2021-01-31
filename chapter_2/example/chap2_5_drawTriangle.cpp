#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <memory>
#include "readShaderSource.h"
#include "saveImage.h"
using namespace std;

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];
bool saveImg = false;

GLuint createShaderProgram();

void init(GLFWwindow* window);

void display(GLFWwindow* window, double currentTime);

int main(int argc, char** argv) {
    if (!glfwInit()) {
        cout << "failed to initialize GLFW..." << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Initialize windows..." << endl;
    // opengl version is 4.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(600, 600, "chap2_5_drawTriangle", NULL, NULL);
    glfwMakeContextCurrent(window);

    cout << "Initialize GLEW..." << endl;
    // used for generate vertex
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "failed to initialize GLEW..." << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Setup swap interval..." << endl;
    glfwSwapInterval(5);

    cout << "Enter init..." << endl;
    init(window);

    cout << "Enter loop shader..." << endl;
    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cout << "Destroy window..." << endl;
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

    return 0;
}

GLuint createShaderProgram() {
    shared_ptr<ReadShaderSource> pReadShaderSource = make_shared<ReadShaderSource>();
    string vshaderSource = pReadShaderSource->runReadShaderSource("./config/vertShaderTri.glsl");
    string fshaderSource = pReadShaderSource->runReadShaderSource("./config/fragShader.glsl");
    const char* vshaderSourceStr = vshaderSource.c_str();
    const char* fshaderSourceStr = fshaderSource.c_str();

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint vfProgram = glCreateProgram();

    glShaderSource(vShader, 1, &vshaderSourceStr, NULL);
    glShaderSource(fShader, 1, &fshaderSourceStr, NULL);
    glCompileShader(vShader);
    glCompileShader(fShader);

    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);

    return vfProgram;
}

void init(GLFWwindow* window) {

    renderingProgram = createShaderProgram();

    // should add GLEW initialization especially glewExperimental
    glGenVertexArrays(numVAOs, vao);

    glBindVertexArray(vao[0]);
}

void display(GLFWwindow* window, double currentTime) {
    glClear(GL_DEPTH_BUFFER_BIT);
    // it should clear the screen first
    // we use black to fill the screen
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);

    // draw point
    glDrawArrays(GL_TRIANGLES, 0, 3);

    if (!saveImg) {
        shared_ptr<SaveImage> psaveImg = make_shared<SaveImage>();
        string outputPath = "./result/drawTriangle.png";
        psaveImg->runSaveImage(outputPath);
        saveImg = true;
    }
}