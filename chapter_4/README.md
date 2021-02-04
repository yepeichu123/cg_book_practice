# Result——Designed by peichu Ye

1. **drawCube**

In this section, we draw a yellow cube which uses buffer to load the vertices.

![drawCube](result/drawCube.png)



2. **drawCubeColor**

To modify the color of the cube, we use the different shaders which outputs the varyingColor to the fragment shader.

![drawCubeColor](result/drawCubeColor.png)



3. **drawCubeRotate**

The uniform values are used to transform the transformation matrix from vertices shader to buffers.

![drawCubeRotate](result/drawCubeRotate.png)
![drawCubeRotate_1](result/drawCubeRotate_1.png)
![drawCubeRotate_2](result/drawCubeRotate_2.png)
![drawCubeRotate_3](result/drawCubeRotate_3.png)



4. **drawMultipleCubes**

To draw 24 cubes, we set a loop with 24 times.

![drawMultipleCubes_1](result/drawMultipleCubes_1.png)



5. **drawMultipleCubesInstance**

In this section, we replace "glDrawArrays" with "glDrawArraysInstanced" to create many instances. Note that we modify many codes in vertices shader even we write many functions.

![drawMultipleCubesInstance_1](result/drawMultipleCubesInstance_1.png)
![drawMultipleCubesInstance_2](result/drawMultipleCubesInstance_2.png)
![drawMultipleCubesInstance_3](result/drawMultipleCubesInstance_3.png)


6. **drawMultipleGeometries**

We use two buffers to save cube and pyramid. Note that we should declear two model vertices in init() function. And transform the view-model matrix to the vertices shader.

![drawMultipleGeometries](result/drawMultipleGeometries_1.png)


7. **drawPlanets**

In this section, we build a simulated solar system and two buffers are used.

![drawPlanets_1](result/drawPlanets_1.png)
![drawPlanets_2](result/drawPlanets_2.png)
![drawPLanets_3](result/drawPlanets_3.png)