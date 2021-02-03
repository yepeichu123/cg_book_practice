
set(LINK_LIBS 
    ${OPENGL_LIBRARY}
    -lGLEW
    -lglfw
    ${OpenCV_LIBS}
    Utils
)

# draw cube
add_executable(chap4_1_drawCube chap4_1_drawCube.cpp)
target_link_libraries(chap4_1_drawCube
    ${LINK_LIBS}
)

# draw colorful cube
add_executable(chap4_2_drawCubeColor chap4_2_drawCubeColor.cpp)
target_link_libraries(chap4_2_drawCubeColor
    ${LINK_LIBS}
)

# draw moving colorful cube
add_executable(chap4_3_drawCubeRotate chap4_3_drawCubeRotate.cpp)
target_link_libraries(chap4_3_drawCubeRotate
    ${LINK_LIBS}
)