# the test program need GLUT
# test
add_executable(test test.cpp)
target_link_libraries(test ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

set(LIBS 
    ${OPENGL_LIBRARY} 
    -lglfw 
    -lGLEW
    ${OpenCV_LIBS}
    Utils
)

# chap_2_1_background
add_executable(chap2_1_background 
    chap2_1_background.cpp
)
target_link_libraries(chap2_1_background 
    ${LIBS}
)

# chap_2_2_drawPoint
add_executable(chap2_2_drawPoint 
    chap2_2_drawPoint.cpp
)
target_link_libraries(chap2_2_drawPoint 
    ${OPENGL_LIBRARY} 
    -lglfw 
    -lGLEW
    ${OpenCV_LIBS}
    Utils
)

# chap_2_3_detectException
add_executable(chap2_3_detectException 
    chap2_3_detectException.cpp
)
target_link_libraries(chap2_3_detectException 
    ${OPENGL_LIBRARY} 
    -lglfw 
    -lGLEW
    Utils
)

# chap_2_4_readShaderSource
add_executable(chap2_4_readShaderSource
    chap2_4_readShaderSource.cpp
)
target_link_libraries(chap2_4_readShaderSource
    ${OPENGL_LIBRARY}
    -lglfw 
    -lGLEW
    Utils
)

# chap2_5_drawTriangle
add_executable(chap2_5_drawTriangle
    chap2_5_drawTriangle.cpp
)
target_link_libraries(chap2_5_drawTriangle
    ${OPENGL_LIBRARY}
    -lglfw
    -lGLEW
    Utils
)

# chap2_6_tiangleMoving
add_executable(chap2_6_triangleMoving
    chap2_6_triangleMoving.cpp
)
target_link_libraries(chap2_6_triangleMoving
    ${OPENGL_LIBRARY}
    -lglfw
    -lGLEW
    Utils
)