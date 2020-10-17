#include "Camera.hpp"

namespace vn {
    mat4<float> &Camera::getProjection() {
        return this->projection_matrix;
    }

    glm::mat4 Camera::getProjection_glm() {
        //return glm::ortho(0.f, 800.f, 600.f, 0.f, 0.f, 1.f);
        return glm::perspective(glm::radians(70.0f), 800.f / 600.f, 0.1f, 5.f);
    }
}