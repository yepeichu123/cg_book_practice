#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "utils.h"
#include <memory>
#include <iostream>
using namespace std;

// vertex array object
#define numVAOs 1
// vertex buffer object
#define numVBOs 2
// rendering program ID
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

// camera position
float cameraX, cameraY, cameraZ;
// cube location
float cubeLocX, cubeLocY, cubeLocZ;
 
// data is used in display function
GLuint mvLoc, projLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat;

// to use common functions
shared_ptr<Utils> pUtils = make_shared<Utils>();

// setup the vertices and activate the vao and vbo
void setupVertices();

// create the rendering shader program and initialize the position of camera and cube.
void init(GLFWwindow* window);

// update the screen real-time
void display(GLFWwindow* window, double currentTime);


int main(int argc, char** argv) {
    cout << "Enter GLFW initialization..." << endl;
    // initialize glfw
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(600, 600, "chapter4_drawCube", NULL, NULL);
    glfwMakeContextCurrent(window);
    cout << "Finshed to initialize GLFW..." << endl;

    cout << "Enter GLEW initialization..." << endl;
    // initialize glew
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        exit(EXIT_FAILURE);
    }
    cout << "Finished to initialize GLEW..." << endl;

    cout << "Set up swap interval..." << endl;
    // setup swap interval
    glfwSwapInterval(1);

    cout << "Initialize window,,," << endl;
    // initialize the shader program
    init(window);

    cout << "Enter loop..." << endl;
    // main shader loop
    while (!glfwWindowShouldClose(window)) {
        // real-time update shader
        display(window, glfwGetTime());
        // swap the buffer and screen
        glfwSwapBuffers(window);
        // deal with the poll events
        glfwPollEvents();
    }

    cout << "Destroy the window..." << endl;
    // deconstruct 
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

    // return 0;
}

void setupVertices() {
    // 36 vertics and 12 triangles 
    // which constructs a cube with 2*2*2.
    float vertexPositions[108] = {
        -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 
        1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f
    };

    // vao is used to control the buffer(vbo)
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);

    // vbo is used as buffer and the first one buffer is activated
    glGenBuffers(numVBOs, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

    // add the data into the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
}

void init(GLFWwindow* window) {
    // create shader program which reads shader from config files and compiles shaders
    renderingProgram = pUtils->runCreateShaderProgram(string("./config/vertShader.glsl"), string("./config/fragShader.glsl"));

    // initialize camera and cube position
    cameraX = 0.0f;
    cameraY = 0.0f;
    cameraZ = 8.0f;

    cubeLocX = 0.0f;
    cubeLocY = -2.0f;
    cubeLocZ = 0.0f;

    setupVertices();
}

// update the screen real-time
void display(GLFWwindow* window, double currentTime) {
    // clear the depth buffer
    glClear(GL_DEPTH_BUFFER_BIT);
    // to activate the shader program
    glUseProgram(renderingProgram);

    // get MV matrix and project matrix 
    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

    // construct the perspective matrix
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    // 1.0472 radians = 60 degrees
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

    // construct view matrix, model matrix and view-model matrix
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));
    mvMat = vMat * mMat;

    // transform perspective matrix and MV matrix to uniform values
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

    // connect VBO with shader
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // modify OpenGL setting and draw model
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}