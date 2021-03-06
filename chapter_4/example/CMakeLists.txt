
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

# draw multiple moving colorful cubes
add_executable(chap4_4_drawMultipleCubes chap4_4_drawMultipleCubes.cpp)
target_link_libraries(chap4_4_drawMultipleCubes
    ${LINK_LIBS}
)

# draw multiple cubes by instances
add_executable(chap4_5_drawMultipleCubesInstance chap4_5_drawMultipleCubesInstance.cpp)
target_link_libraries(chap4_5_drawMultipleCubesInstance
    ${LINK_LIBS}
)

# draw multiple geometries
add_executable(chap4_6_drawMultipleGeometries chap4_6_drawMultipleGeometries.cpp)
target_link_libraries(chap4_6_drawMultipleGeometries
    ${LINK_LIBS}
)

# draw planets
add_executable(chap4_7_drawPlanets chap4_7_drawPlanets.cpp)
target_link_libraries(chap4_7_drawPlanets
    ${LINK_LIBS}
)