#ifndef SAVE_IMAGE_H
#define SAVE_IMAGE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>

class SaveImage
{
public:
    SaveImage();

    ~SaveImage();

    void runSaveImage(std::string& outputPath);
};


#endif