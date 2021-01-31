#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include "exceptionCatch.h"
using namespace std;

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];
GLfloat pointSize = 30.0;

GLuint createShaderProgram();

void init(GLFWwindow* window);

void display(GLFWwindow* window, double currentTime);


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
    GLFWwindow* window = glfwCreateWindow(600, 600, "chap2_3_detectException", NULL, NULL);
    // connect the window with opengl
    glfwMakeContextCurrent(window);

    cout << "Initialize GLEW..." << endl;
    // used for generate vertex
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        cout << "failed to initialize GLEW..." << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Setup swap interval..." << endl;
    glfwSwapInterval(1);

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
    // exception parameters
    GLint vertCompiled;
    GLint fragCompiled;
    GLint linked;
    shared_ptr<ExceptionCatch> pExcepCatch = make_shared<ExceptionCatch>();
    
    const char* vshaderSource = 
        "#version 430       \n"
        "void main(void)    \n"
        "{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";

    const char* fshaderSource = 
        "#version 430       \n"
        "out vec4 color;    \n"
        "void main(void)    \n"
        "{ color = vec4(0.0, 1.0, 0.0, 1.0); }";

    // create the vertex shader and fragment shader
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    // load the char into two shaders and compile
    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);

    // catch compiling error
    glCompileShader(vShader);
    pExcepCatch->checkOpenGLError();
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
    if (vertCompiled != 1) {
        cout << "vertex compilation failed." << endl;
        pExcepCatch->printShaderLog(vShader);
    }

    glCompileShader(fShader);
    pExcepCatch->checkOpenGLError();
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
    if (fragCompiled != 1) {
        cout << "fragment compilation failed." << endl;
        pExcepCatch->printShaderLog(fShader);
    }


    // create the shader program
    GLuint vfProgram = glCreateProgram();

    // load two shaders into program
    // catch linking error
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);
    pExcepCatch->checkOpenGLError();
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if (linked != 1) {
        cout << "linked failed." << endl;
        pExcepCatch->printProgramLog(vfProgram);
    }

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

    glPointSize(pointSize);

    // draw point
    glDrawArrays(GL_POINTS, 0, 1);
}
