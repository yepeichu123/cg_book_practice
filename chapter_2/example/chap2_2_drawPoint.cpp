#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>
#include <memory>
#include <string>
#include "saveImage.h"
using namespace std;

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];
GLfloat incRadius = 5.0;
GLfloat pointSize = 30.0;
GLfloat maxPointSize = 300.0;
GLfloat minPointSize = 5.0;
bool saveImg = false;

GLuint createShaderProgram();

void init(GLFWwindow* window);

void display(GLFWwindow* window, double currentTime);

// void saveImage();

int main(int argc, char** argv) {
    if (!glfwInit()) {
        cout << "failed to initialize GLFW..." << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Initialize windows..." << endl;
    // opengl version is 4.3.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // initialize windows
    GLFWwindow* window = glfwCreateWindow(600, 600, "chap2_2_drawPoint", NULL, NULL);
    // connect the window with opengl
    glfwMakeContextCurrent(window);

    cout << "Initialize GLEW..." << endl;
    // used for generate vertex
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "failed to initialize GLEW..." << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Setup swap interval..." << endl;
    glfwSwapInterval(3);

    cout << "Enter init..." << endl;
    init(window);

    cout << "Enter loop shader..." << endl;
    while (!glfwWindowShouldClose(window)) {
        // draw somethings into the buffer
        display(window, glfwGetTime());
        // swap buffers means that updates window
        glfwSwapBuffers(window);
        // deal with poll events
        glfwPollEvents();
    }

    cout << "Destroy window..." << endl;
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

    return 0;
}

GLuint createShaderProgram() {
    const char* vshaderSource = 
        "#version 430       \n"
        "void main(void)    \n"
        "{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";

    const char* fshaderSource = 
        "#version 430       \n"
        "out vec4 color;    \n"
        "void main(void)    \n"
        "{ if (gl_FragCoord.x < 300) color = vec4(0.0, 1.0, 0.0, 1.0); else color = vec4(1.0, 0.0, 0.0, 1.0); }";
        // "{ color = vec4(1.0, 1.0, 1.0, 1.0); }";

    // create the vertex shader and fragment shader
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    // load the char into two shaders and compile
    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);
    glCompileShader(vShader);
    glCompileShader(fShader);

    // create the shader program
    GLuint vfProgram = glCreateProgram();
    // load two shaders into program
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
    // it should clear the screen first
    // we use black to fill the screen
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);

    // update size of point
    pointSize += incRadius;
    if (pointSize >= maxPointSize) {
        incRadius = -5.0f;
    }
    if (pointSize <= minPointSize) {
        incRadius = 5.0f;
    }
    cout << "Point size: " << pointSize << endl;
    glPointSize(pointSize);

    // draw point
    glDrawArrays(GL_POINTS, 0, 1);

    // save image 
    if (!saveImg) {
        shared_ptr<SaveImage> psaveImg = make_shared<SaveImage>();
        string outputPath = "./result/drawPoint.png";
        psaveImg->runSaveImage(outputPath);
        saveImg = true;
    }
}
