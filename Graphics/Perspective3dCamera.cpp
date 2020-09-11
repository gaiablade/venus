#include "Perspective3dCamera.hpp"

namespace ga {
    Perspective3dCamera::Perspective3dCamera(const perspData &d) {
        this->projection_matrix = mat4<float>::perspective(d);
    }
}
