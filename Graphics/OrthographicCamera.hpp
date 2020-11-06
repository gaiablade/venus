#pragma once
#include "Camera.hpp"
#include "mat4.hpp"
#include "vec2.hpp"

namespace vn {
    class OrthographicCamera : public Camera {
    public:
        OrthographicCamera(const orthoData &params);
        void setPosition(vn::vec2f position);
    protected:
        orthoData params;
    };
}


