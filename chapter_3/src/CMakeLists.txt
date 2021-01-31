
add_library(transformPose SHARED transformPose.cpp)

target_link_libraries(transformPose
    ${OPENGL_LIBS}
)