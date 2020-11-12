#pragma once
#include "Camera.hpp"
#include "mat4.hpp"
#include "vec2.hpp"
#include "vec4.hpp"

namespace vn {
    class OrthographicCamera : public Camera {
    public:
        OrthographicCamera(const orthoData &params);
        void setPosition(vn::vec2f position);
        void clip(const vec4f& clipCoordinates);
    protected:
        orthoData params;
        vec2f position;
        vec4f v_ClipCoordinates{};
        bool b_CheckClip{false};
    };
}


