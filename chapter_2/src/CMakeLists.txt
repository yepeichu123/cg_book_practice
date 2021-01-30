# the test program need GLUT
# test
add_executable(test test.cpp)
target_link_libraries(test ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

# chap_2_1_background
add_executable(chap2_1_background 
    chap2_1_background.cpp
    saveImage.cpp)
target_link_libraries(chap2_1_background 
    ${OPENGL_LIBRARY} 
    -lglfw 
    -lGLEW
    ${OpenCV_LIBS}
)

# chap_2_2_drawPoint
add_executable(chap2_2_drawPoint 
    chap2_2_drawPoint.cpp
    saveImage.cpp
)
target_link_libraries(chap2_2_drawPoint 
    ${OPENGL_LIBRARY} 
    -lglfw 
    -lGLEW
    ${OpenCV_LIBS}
)

# chap_2_3_detectException
add_executable(chap2_3_detectException 
    chap2_3_detectException.cpp
    exceptionCatch.cpp
)
target_link_libraries(chap2_3_detectException 
    ${OPENGL_LIBRARY} 
    -lglfw 
    -lGLEW
)

# chap_2_4_readShaderSource
add_executable(chap2_4_readShaderSource
    chap2_4_readShaderSource.cpp
)
target_link_libraries(chap2_4_readShaderSource
    ${OPENGL_LIBRARY}
    -lglfw 
    -lGLEW
)