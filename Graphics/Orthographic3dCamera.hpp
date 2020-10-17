#pragma once
#include "Camera.hpp"

namespace vn {
    class Orthographic3dCamera : public Camera {
    public:
        Orthographic3dCamera(const orthoData& params);
    };
}

