cmake_minimum_required(VERSION 2.8)
project(chapter_2)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "-g -Wall")

# test
add_executable(test test.cpp)
target_link_libraries(test ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

# chap_2_1_background
add_executable(chap2_1_background chap2_1_background.cpp)
target_link_libraries(chap2_1_background ${GLUT_LIBRARY} ${OPENGL_LIBRARY} -lglfw -lGLEW)

# chap_2_2_drawPoint
add_executable(chap2_2_drawPoint chap2_2_drawPoint.cpp)
target_link_libraries(chap2_2_drawPoint ${OPENGL_LIBRARY} -lglfw -lGLEW)