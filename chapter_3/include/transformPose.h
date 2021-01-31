#ifndef TRANSFORM_POSE_H
#define TRANSFORM_POSE_H

#include <glm/glm.hpp>

class TransformPose {
public:
    TransformPose();

    ~TransformPose();

    // construct and return translation matrix
    glm::mat4 buildTranslate(const float& x, const float& y, const float& z);

    // construct rotation matrix along x axis
    glm::mat4 buildRotateX(const float& rad);

    // construct rotation matrix along y axis
    glm::mat4 buildRotateY(const float& rad);

    // construct rotation matrix along z axis
    glm::mat4 buildRotateZ(const float& rad);

    // construct and return scale matrix
    glm::mat4 buildScale(const float& x, const float& y, const float& z);
};


#endif 