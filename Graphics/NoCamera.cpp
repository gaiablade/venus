#include "NoCamera.hpp"

namespace ga {
    NoCamera::NoCamera() {
        this->projection_matrix = mat4<float>::identity();
    }
}
