#include "readShaderSource.h"
#include <iostream>

ReadShaderSource::ReadShaderSource() {

}

ReadShaderSource::~ReadShaderSource() {

}

// input: filePath to read the file
// output: the content is read from source file
std::string ReadShaderSource::runReadShaderSource(const std::string& filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);
    if (!fileStream.is_open()) {
        std::cout << "Failed to open the source file:\n"
            << filePath << "\n"
            << "Please check your path." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    std::string line = "";
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();
    return content;
}