#include "saveImage.h"


SaveImage::SaveImage() {

}

SaveImage::~SaveImage() {

}

void SaveImage::runSaveImage(std::string& outputPath) {
    // to get size of the window
    GLint viewPort[4] = {0};
    glGetIntegerv(GL_VIEWPORT, viewPort);
    int winRows = viewPort[3];
    int winCols = viewPort[2];

    // to read pixels of window
    GLbyte *colorArr = new GLbyte[winRows * winCols * 3];
    glReadPixels(viewPort[0], viewPort[1], viewPort[2], viewPort[3], GL_RGB, GL_UNSIGNED_BYTE, colorArr);
    // reset invalid value
    for (int i = 0; i < winRows*winCols*3; ++i) {      
        if (colorArr[i] == -1) {
            colorArr[i] = 255;
        }
    }

    // convert to image of OpenCV
    cv::Mat image = cv::Mat(winRows, winCols, CV_8UC3, cv::Scalar::all(0));
    for (int i = 0; i < winRows; ++i) {
        for (int j = 0; j < winCols; ++j) {
            // the origin locates at the left bottom in buffers
            // so we should make the right convertion
            image.at<cv::Vec3b>(winRows-i-1, j) = cv::Vec3b(colorArr[(i*winCols+j)*3+2], colorArr[(i*winCols+j)*3+1], colorArr[(i*winCols+j)*3]);
        }
    }

    delete colorArr;

    // output
    cv::imwrite(outputPath, image);
}