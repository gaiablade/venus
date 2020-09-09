#pragma once
#include "Camera.hpp"
#include "mat4.hpp"

namespace ga {
    class OrthographicCamera : public Camera {
    public:
        OrthographicCamera(const orthoData &params);

    protected:
    };
}


