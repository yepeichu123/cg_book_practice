add_library(Utils SHARED
    ${PROJECT_SOURCE_DIR}/src/saveImage.cpp
    ${PROJECT_SOURCE_DIR}/src/readShaderSource.cpp
    ${PROJECT_SOURCE_DIR}/src/exceptionCatch.cpp
)

target_link_libraries(Utils
    ${OPENGL_LIBRARY} 
    -lglfw 
    -lGLEW
    ${OpenCV_LIBS}
)