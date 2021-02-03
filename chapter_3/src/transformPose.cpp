#include "transformPose.h"

TransformPose::TransformPose() {

}

TransformPose::~TransformPose() {

}

// construct and return translation matrix
glm::mat4 TransformPose::buildTranslate(const float& x, const float& y, const float& z) {
    glm::mat4 trans = glm::mat4(
        1.0, 0.0, 0.0, 0.0,     // first column
        0.0, 1.0, 0.0, 0.0,     // second column
        0.0, 0.0, 1.0, 0.0,     // third column
        x, y, z, 1.0            // fourth column
    );
    return trans;
}

// construct rotation matrix along x axis
glm::mat4 TransformPose::buildRotateX(const float& rad) {
    glm::mat4 xrot = glm::mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, cos(rad), -sin(rad), 0.0,
        0.0, sin(rad), cos(rad), 0.0,
        0.0, 0.0, 0.0, 1.0
    );
    return xrot;
}

// construct rotation matrix along y axis
glm::mat4 TransformPose::buildRotateY(const float& rad) {
    glm::mat4 yrot = glm::mat4(
        cos(rad), 0.0, sin(rad), 0.0,
        0.0, 1.0, 0.0, 0.0,
        -sin(rad), 0.0, cos(rad), 0.0,
        0.0, 0.0, 0.0, 1.0
    );
    return yrot;
}

// construct rotation matrix along z axis
glm::mat4 TransformPose::buildRotateZ(const float& rad) {
    glm::mat4 zrot = glm::mat4(
        cos(rad), sin(rad), 0.0, 0.0,
        -sin(rad), cos(rad), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
    return zrot;
}

// construct and return scale matrix
glm::mat4 TransformPose::buildScale(const float& x, const float& y, const float& z) {
    glm::mat4 scale = glm::mat4(
        x, 0.0, 0.0, 0.0,
        0.0, y, 0.0, 0.0,
        0.0, 0.0, z, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
    return scale;
}