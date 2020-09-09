#pragma once
#include "Camera.hpp"
#include "mat4.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ga {
    class Perspective3dCamera : public Camera{
    public:
        explicit Perspective3dCamera(const perspData&);
    };
}


