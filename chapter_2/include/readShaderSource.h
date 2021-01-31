#ifndef READ_SHADER_SOURCE_H
#define READ_SHADER_SOURCE_H

#include <string>
#include <fstream>

class ReadShaderSource {
public:
    ReadShaderSource();

    ~ReadShaderSource();

    // input: filePath to read the file
    // output: the content is read from source file
    std::string runReadShaderSource(const std::string& filePath);    
};


#endif