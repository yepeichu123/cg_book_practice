#include "transformPose.h"
#include <glm/glm.hpp>
#include <memory>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    shared_ptr<TransformPose> ptrans = make_shared<TransformPose>();

    glm::vec4 pw = glm::vec4(1.0, 0.0, 0.0, 1.0);
    // translate point
    glm::vec4 pc = ptrans->buildTranslate(1.0, 1.0, 1.0) * pw;
    cout << "Before translating, pw: " << pw.x/pw.w << " " << pw.y/pw.w << " " << pw.z/pw.w  
        << ", after translating, pc: " << pc.x/pc.w << " " << pc.y/pc.w << " " << pc.z/pc.w   << endl;

    // rotate point along z axis
    pc = ptrans->buildRotateZ(M_PI_4) * pw;
    cout << "\nBefore rotating along z, pw: " << pw.x/pw.w << " " << pw.y/pw.w << " " << pw.z/pw.w  
        << ", after rotating, pc: " << pc.x/pc.w << " " << pc.y/pc.w << " " << pc.z/pc.w   << endl;

    // scale point
    pc = ptrans->buildScale(0.5, 0.5, 0.5) * pw;
    cout << "\nBefore scaling (0.5, 0.5, 0.5), pw: " << pw.x/pw.w << " " << pw.y/pw.w << " " << pw.z/pw.w  
        << ", after scaling, pc: " << pc.x/pc.w << " " << pc.y/pc.w << " " << pc.z/pc.w   << endl;

    return 0;
}