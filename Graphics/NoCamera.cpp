#include "NoCamera.hpp"

namespace vn {
    NoCamera::NoCamera() {
        this->projection_matrix = mat4<float>::identity();
    }
}
