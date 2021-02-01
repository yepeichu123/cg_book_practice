
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC)

add_library(Utils SHARED ${SRC})

target_link_libraries(Utils 
    ${OPENGL_LIBRARY}
    -lGLEW
    -lglfw
)