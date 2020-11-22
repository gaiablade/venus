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
        mat4f& getView();
        mat4f& getProjection();
        static glm::mat4 getProjection_glm();
    protected:
        /**
         * MVP computed by multiplying projection matrix with model-view matrix
         */
         mat4f view_matrix;
         mat4f projection_matrix;
    };
}
