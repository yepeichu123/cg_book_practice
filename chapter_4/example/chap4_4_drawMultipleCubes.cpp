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
#define numVBOs 1
// rendering program ID
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

// camera position
float cameraX, cameraY, cameraZ;
 
// data is used in display function
GLuint mvLoc, projLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat, tMat, rMat;

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
    GLFWwindow* window = glfwCreateWindow(600, 600, "chapter4_4_drawMultipleCubes", NULL, NULL);
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
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);

    // vbo is used as buffer and the first one buffer is activated
    glGenBuffers(numVBOs, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

    // add the data into the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
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
    // We delete the cube location because we should always change their location
    // Here, we set the camera position with z = 32.0f and then the cube looks like very small because we observe it far away.
    // initialize camera and cube position
    cameraX = 0.0f;
    cameraY = 0.0f;
    cameraZ = 32.0f;

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
    
    for (int i = 0; i < 24; ++i) {
        // time
        double tf = currentTime + i;

        // modify transformation
        // here, we setup the translation as 8 * time, which separates all cubes far away.
        tMat = glm::translate(glm::mat4(1.0f),
            glm::vec3(sin(0.35f*tf)*8.0f, cos(0.52f*tf)*8.0f, sin(0.7f*tf)*8.0f));
        rMat = glm::rotate(glm::mat4(1.0f), 1.75f*(float)tf, glm::vec3(0.0f, 1.0f, 0.0f));
        rMat = glm::rotate(rMat, 1.75f*(float)tf, glm::vec3(1.0f, 0.0f, 0.0f));
        rMat = glm::rotate(rMat, 1.75f*(float)tf, glm::vec3(0.0f, 0.0f, 1.0f));

        // construct view matrix, model matrix and view-model matrix
        vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
        mMat = tMat * rMat;
        mvMat = vMat * mMat;

        // transform perspective matrix and MV matrix to uniform values
        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

        // connect VBO with shader
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
        glEnableVertexAttribArray(0);

        // modify OpenGL setting and draw model
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    ++indexSaveImg;
    // save image 
    if (indexSaveImg == 5000 && saveImgTimes < 3) {
        string imgPath = "./result/drawMultipleCubes";
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