// glew means OpenGL Extension Wrangler
// glfw means graphics Library Framework, which is used for 3D drawing 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>
#include <memory>
#include <string>
// #include <opencv2/core.hpp>
// #include <opencv2/highgui.hpp>
#include "saveImage.h"

using namespace std;

bool saveImg = false;
// void saveImage();

// empty initial function 
void init(GLFWwindow* window) {

}

void display(GLFWwindow* window, double currentTime) {
    glClearColor(0.5, 0.5, 0.5, 1.0);
    // clear all color buffers and update by the predefined color
    glClear(GL_COLOR_BUFFER_BIT);
    // save image 
    if (!saveImg) {
        // saveImage();
        shared_ptr<SaveImage> psaveImg = make_shared<SaveImage>();
        string outputPath = "./outputPath.png";
        psaveImg->runSaveImage(outputPath);
        saveImg = true;
    }
}

int main(int argc, char** argv) {

    // failed to initialize and exit
    if (!glfwInit()) {
        cout << "test glfwInit...\n" << "sorry, it failed." << endl;
        exit(EXIT_FAILURE);
    }
    // create object
    // hint function aims to point out the opengl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(600, 600, "chap2_1_background", NULL, NULL);

    // update the connection
    glfwMakeContextCurrent(window);

    // initialize GLEW
    if (glewInit() != GLEW_OK) {
        cout << "test glfwInit...\n" << "sorry, it failed." << endl;
        exit(EXIT_FAILURE);
    }

    // This function sets the swap interval for the current OpenGL
    glfwSwapInterval(1);

    // initialize the window
    init(window);

    // repeat calling display
    while (!glfwWindowShouldClose(window)) {
        // cout << "enter display function..." << endl;

        display(window, glfwGetTime());
        // draw 
        glfwSwapBuffers(window);
        // process window events such as key-button 
        glfwPollEvents();
    }

    // release
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

    return 0;
}

// void saveImage() {
//     // to get size of the window
//     GLint viewPort[4] = {0};
//     glGetIntegerv(GL_VIEWPORT, viewPort);
//     int winRows = viewPort[3];
//     int winCols = viewPort[2];

//     // to read pixels of window
//     GLbyte *colorArr = new GLbyte[winRows * winCols * 3];
//     glReadPixels(viewPort[0], viewPort[1], viewPort[2], viewPort[3], GL_RGB, GL_UNSIGNED_BYTE, colorArr);
//     // reset invalid value
//     for (int i = 0; i < winRows*winCols*3; ++i) {      
//         if (colorArr[i] == -1) {
//             colorArr[i] = 255;
//         }
//     }

//     // convert to image of OpenCV
//     Mat image = Mat(winRows, winCols, CV_8UC3, Scalar::all(0));
//     for (int i = 0; i < winRows; ++i) {
//         for (int j = 0; j < winCols; ++j) {
//             // the origin locates at the left bottom in buffers
//             // so we should make the right convertion
//             image.at<Vec3b>(winRows-i-1, j) = Vec3b(colorArr[(i*winCols+j)*3+2], colorArr[(i*winCols+j)*3+1], colorArr[(i*winCols+j)*3]);
//         }
//     }

//     delete colorArr;

//     // output
//     imwrite("chap2_1.png", image);
// }