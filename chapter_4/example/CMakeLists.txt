
add_executable(chap4_1_drawCube chap4_1_drawCube.cpp)
target_link_libraries(chap4_1_drawCube
    ${OPENGL_LIBRARY}
    -lGLEW
    -lglfw
    ${OpenCV_LIBS}
    Utils
)