#include "Orthographic3dCamera.hpp"

namespace ga {
    Orthographic3dCamera::Orthographic3dCamera(const orthoData &params) {
        this->projection_matrix = mat4<float>::ortho3d(params);
    }
}
