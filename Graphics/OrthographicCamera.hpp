#pragma once
#include "Camera.hpp"
#include "mat4.hpp"
#include "vec2.hpp"
#include "vec4.hpp"

namespace vn {
    const float zoomIncrement = 1.f;

    class OrthographicCamera : public Camera {
    public:
        OrthographicCamera(const orthoData &params);
        void setPosition(vn::vec2f position);
        void clip(const vec4f& clipCoordinates);
        void setZoom(float zoom);
    protected:
        orthoData params;
        orthoData transformedParams;
        vec2f position;
        float zoom{1.f};
        vec4f v_ClipCoordinates{};
        bool b_CheckClip{false};
    };
}


