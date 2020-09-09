#pragma once
#include "Camera.hpp"

namespace ga {
    class Orthographic3dCamera : public Camera {
    public:
        Orthographic3dCamera(const orthoData& params);
    };
}

