# Result——Designed by peichu Ye

1. **background**

![chap2_1_background](result/background.png)


2. **drawPoint**

![chap2_2_drawPoint](result/drawPoint.png)


3. **detectException**

Note that there is an error occurs after glewInit(), but it doesn't matters because we can find the declaration on the [website](https://www.khronos.org/opengl/wiki/OpenGL_Loading_Library).


4. **readShaderSource**

We add a funtion to read shader source from files which is useful in the next program. And you can modified the position and color in the config files.


5. **drawTriangle**

In this part, we draw a triangle, we first draw a right triangle and then draw an isosceles triangle which is the practice in this chapter.

![chap2_5_drawTriangle](result/drawTriangle.png)


6. **drawTriangleMoving**

In this section, we modified the vertex shader file, and we draw a moving square. If you want to draw a triangle, please modified the shader file.

![chap2_6_triangleMovingLeft](result/triangleMovingLeft.png)
![chap2_6_triangleMovingCenter](result/triangleMovingCenter.png)
![chap2_6_triangleMovingRight](result/triangleMovingRight.png)