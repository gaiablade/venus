#include "OrthographicCamera.hpp"

namespace vn {
    OrthographicCamera::OrthographicCamera(const orthoData &params) :
    params(params)
    {
        this->projection_matrix = mat4<float>::ortho2d(params);
    }

    void OrthographicCamera::setPosition(vn::vec2f position) {
        this->projection_matrix = mat4f::translate2d(vec2f(-position.x, -position.y)) * mat4f::ortho2d(params);
    }
}
