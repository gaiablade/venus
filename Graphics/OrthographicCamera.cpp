#include "OrthographicCamera.hpp"

namespace ga {
    OrthographicCamera::OrthographicCamera(const orthoData &params) {
        this->projection_matrix = mat4<float>::ortho2d(params);
    }
}
