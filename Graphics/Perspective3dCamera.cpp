#include "Perspective3dCamera.hpp"

namespace ga {
    Perspective3dCamera::Perspective3dCamera(const perspData &d) {
        //auto g = glm::perspective(0, 0, 0, 0);
        this->projection_matrix = mat4<float>::perspective(d);
    }
}
