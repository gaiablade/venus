#include "Perspective3dCamera.hpp"

namespace vn {
    Perspective3dCamera::Perspective3dCamera(const perspData &d) {
        this->projection_matrix = mat4<float>::perspective(d);
    }
}
