#include "Perspective3dCamera.hpp"

namespace vn {
    Perspective3dCamera::Perspective3dCamera(const perspData &d) {
        this->view_matrix = mat4f::identity();
        this->projection_matrix = mat4f::perspective(d);
    }
}
