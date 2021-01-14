#include "OrthographicCamera.hpp"

namespace vn {
    OrthographicCamera::OrthographicCamera(const orthoData &params) :
    params(params),
    transformedParams(params)
    {
        this->view_matrix = mat4f::identity();
        this->projection_matrix = mat4<float>::ortho2d(params);
    }

    void OrthographicCamera::setPosition(vn::vec2f m_position) {
        // clipCoordinates = (left, top, right, bottom)
        vec2f clippedPosition = m_position;
        // If clipping has been enabled and the set view's dimensions fit within the clip dimensions, clip the view into the boundaries:
        if (b_CheckClip && transformedParams.width <= v_ClipCoordinates.z - v_ClipCoordinates.x && transformedParams.height <= v_ClipCoordinates.w - v_ClipCoordinates.y) {
            if (clippedPosition.x - (transformedParams.width / 2) < v_ClipCoordinates.x) {
                clippedPosition.x = v_ClipCoordinates.x + (transformedParams.width / 2);
            } else if (clippedPosition.x + (transformedParams.width / 2) > v_ClipCoordinates.z) {
                clippedPosition.x = v_ClipCoordinates.z - (transformedParams.width / 2);
            }
            if (clippedPosition.y - (transformedParams.height / 2) < v_ClipCoordinates.y) {
                clippedPosition.y = v_ClipCoordinates.y + (transformedParams.height / 2);
            } else if (clippedPosition.y + (transformedParams.height / 2) > v_ClipCoordinates.w) {
                clippedPosition.y = v_ClipCoordinates.w - (transformedParams.height / 2);
            }
        }
        this->position = clippedPosition;
        this->view_matrix = mat4f::translate2d(vec2f(-clippedPosition.x, -clippedPosition.y));
    }

    void OrthographicCamera::clip(const vec4f &clipCoordinates) {
        this->v_ClipCoordinates = clipCoordinates;
        this->b_CheckClip = true;
    }

    void OrthographicCamera::setZoom(float zoom) {
        this->zoom = zoom;
        float aspect = params.height/params.width;
        float zoomedW = params.width - ((zoom - 1) * zoomIncrement);
        float zoomedH = zoomedW * aspect;
        vec2f center = vec2f(0, 0);
        transformedParams = orthoData(center.x - zoomedW/2, center.x + zoomedW/2, center.y - zoomedH/2, center.y + zoomedH/2,
                                      params.n, params.f);
        this->projection_matrix = mat4f::ortho2d(transformedParams);
        setPosition(position);
    }
}
