cmake_minimum_required(VERSION 2.8)
project(chapter_3)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

find_package(OpenGL REQUIRED)
find_package(OpenCV REQUIRED)
include_directories(
    ${OPENGL_INCLUDE_DIR}
    ${OpenCV_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/example)