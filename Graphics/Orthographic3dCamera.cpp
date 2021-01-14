#include "Orthographic3dCamera.hpp"

namespace vn {
    Orthographic3dCamera::Orthographic3dCamera(const orthoData &params) {
        this->projection_matrix = mat4f::ortho3d(params);
        this->view_matrix = mat4f::identity();
    }
}
