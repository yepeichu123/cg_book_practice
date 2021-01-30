cmake_minimum_required(VERSION 2.8)
project(chapter_2)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

find_package(OpenGL REQUIRED)
# if you want to save image
find_package(OpenCV REQUIRED)
# if you want to run test code
find_package(GLUT REQUIRED)

include_directories(
    ${OPENGL_INCLUDE_DIR}
    ${GLUT_INCLUDE_DIR}
    ${OpenCV_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)