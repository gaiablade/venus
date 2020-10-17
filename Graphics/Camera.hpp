#pragma once
#include "mat4.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

/**
 * Base Camera Class
 */
namespace vn {
    class Camera {
    public:
        mat4<float> &getProjection();
        static glm::mat4 getProjection_glm();

    protected:
        /**
         * MVP computed by multiplying projection matrix with model-view matrix
         */
        mat4<float> projection_matrix;
    };
}
