#include "OrthographicCamera.hpp"

namespace vn {
    OrthographicCamera::OrthographicCamera(const orthoData &params) :
    params(params)
    {
        this->projection_matrix = mat4<float>::ortho2d(params);
    }

    void OrthographicCamera::setPosition(vn::vec2f position) {
        vec2f clippedPosition = position;
        if (b_CheckClip) {
            if (clippedPosition.x < v_ClipCoordinates.x) {
                clippedPosition.x = v_ClipCoordinates.x;
            } else if (clippedPosition.x + (params.r - params.l) > v_ClipCoordinates.z) {
                clippedPosition.x = v_ClipCoordinates.z - (params.r - params.l);
            }
            if (clippedPosition.y < v_ClipCoordinates.y) {
                clippedPosition.y = v_ClipCoordinates.y;
            } else if (clippedPosition.y + (params.b - params.t) > v_ClipCoordinates.w) {
                clippedPosition.y = v_ClipCoordinates.w - (params.b - params.t);
            }
        }
        this->projection_matrix = mat4f::translate2d(vec2f(-clippedPosition.x, -clippedPosition.y)) * mat4f::ortho2d(params);
    }

    void OrthographicCamera::clip(const vec4f &clipCoordinates) {
        this->v_ClipCoordinates = clipCoordinates;
        this->b_CheckClip = true;
    }
}
