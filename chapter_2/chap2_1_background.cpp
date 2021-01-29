// glew means OpenGL Extension Wrangler
// glfw means graphics Library Framework, which is used for 3D drawing 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

// empty initial function 
void init(GLFWwindow* window) {

}

void display(GLFWwindow* window, double currentTime) {
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
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