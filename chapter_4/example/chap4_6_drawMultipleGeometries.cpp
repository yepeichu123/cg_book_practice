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
// 2 vertex buffer objects because we need to draw 2 geometries
#define numVBOs 2
// rendering program ID
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

// camera position
float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;
float pyramidLocX, pyramidLocY, pyramidLocZ;

// data is used in display function
GLuint mvLoc, projLoc, tfLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat, tMat, rMat;
float timeFactor;

// save image flag and index 
GLuint indexSaveImg = 0;
GLuint saveImgTimes = 0;

// to use common functions
shared_ptr<Utils> pUtils = make_shared<Utils>();

// setup the vertices and activate the vao and vbo
void setupVertices();

// create the rendering shader program and initialize the position of camera and cube.
void init(GLFWwindow* window);

// update the screen real-time
void display(GLFWwindow* window, double currentTime);

// modified window size
void windowSizeCallback(GLFWwindow* win, int newWidth, int newHeight);


int main(int argc, char** argv) {
    cout << "Enter GLFW initialization..." << endl;
    // initialize glfw
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(600, 600, "chapter4_6_drawMultipleGeometries", NULL, NULL);
    glfwMakeContextCurrent(window);

    cout << "Enter GLEW initialization..." << endl;
    // initialize glew
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        exit(EXIT_FAILURE);
    }

    cout << "Set up swap interval..." << endl;
    // setup swap interval
    glfwSwapInterval(1);

    cout << "Initialize window..." << endl;
    // initialize the shader program
    init(window);

    // auto-adjust window size
    glfwSetWindowSizeCallback(window, windowSizeCallback);

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
    float cubePositions[108] = {
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

    // 18 vertices and 6 triangles
    // which constructs a pyramid
    float pyramidPosition[54] = {
        // front
        -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 
        // right
        1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 
        // hinder
        1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 
        // left
        -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 
        // bottom-left
        -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 
        // bottom-right
        1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 
    };

    // vao is used to control the buffer(vbo)
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);

    // vbo is used as buffer
    glGenBuffers(numVBOs, vbo);

    // activate the first buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    // add the data into the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubePositions), cubePositions, GL_STATIC_DRAW);

    // activate the second buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    // add the data into the second buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidPosition), pyramidPosition, GL_STATIC_DRAW);
}

void init(GLFWwindow* window) {
    // create shader program which reads shader from config files and compiles shaders
    renderingProgram = pUtils->runCreateShaderProgram(
        string("./config/vertShaderColor.glsl"), string("./config/fragShaderColor.glsl"));

    // construct the perspective matrix
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;

    // 1.0472 radians = 60 degrees
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

    // Note:
    // initialize camera and cube position
    cameraX = 0.0f;
    cameraY = 0.0f;
    cameraZ = 8.0f;

    pyramidLocX = 0.0f;
    pyramidLocY = -2.0f;
    pyramidLocZ = 0.0f;

    cubeLocX = 2.0f;
    cubeLocY = 2.0f;
    cubeLocZ = 0.0f;

    setupVertices();
}

// update the screen real-time
void display(GLFWwindow* window, double currentTime) {
    // clear the depth buffer
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
    // to activate the shader program
    glUseProgram(renderingProgram);

    // get MV matrix and project matrix 
    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

    // construct view matrix, model matrix and view-model matrix
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));


    // cube
    // construct view-model matrix
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

    
    // pyramid
    // construct view-model matrix
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(pyramidLocX, pyramidLocY, pyramidLocZ));
    mvMat = vMat * mMat;

    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, 18);

    ++indexSaveImg;
    // save image 
    if (indexSaveImg == 5000 && saveImgTimes < 3) {
        string imgPath = "./result/drawMultipleGeometries";
        if (saveImgTimes == 0) {
            imgPath += "_1.png";
        }
        else if (saveImgTimes == 1) {
            imgPath += "_2.png";
        }
        else {
            imgPath += "_3.png";
        }
        pUtils->runSaveImage(imgPath);
        cout << "Saved as image in " << imgPath << endl;
        indexSaveImg = 0;
        ++saveImgTimes;
    }
}

void windowSizeCallback(GLFWwindow* win, int newWidth, int newHeight) {
	aspect = (float)newWidth / (float)newHeight;
	glViewport(0, 0, newWidth, newHeight);
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}