#include "Rect.hpp"

namespace vn {
    Rect::Rect(const vec2<float> &dimensions) :
            indices({0, 1, 2, 3, 1, 2}),
            buffer({
                           // position                           // color
                           -dimensions.x / 2, dimensions.y / 2, 1.0f, 0.0f, 0.0f,
                           -dimensions.x / 2, -dimensions.y / 2, 0.0f, 1.0f, 0.0f,
                           dimensions.x / 2, dimensions.y / 2, 0.0f, 0.0f, 1.0f,
                           dimensions.x / 2, -dimensions.y / 2, 0.5f, 0.5f, 0.5f


                   }),
            vbuffer(static_cast<const void *>(buffer.data()), buffer.size() * sizeof(float)),
            ibuffer(static_cast<const void *>(indices.data()), indices.size() * sizeof(uint32_t)),
            dimensions(dimensions)
    {
        this->attributes.Insert<float>(2);
        this->attributes.Insert<float>(3);
        this->varray.addBuffer(this->vbuffer, this->attributes);
    }

    void Rect::Bind() const {
        this->varray.Bind();
        this->ibuffer.Bind();
    }

    IBuffer &Rect::getIBuffer() {
        return this->ibuffer;
    }

    std::array<uint32_t, 6> Rect::getIndices() const {
        return this->indices;
    }

    mat4<float> Rect::getModelView() const {
        mat4<float> scaleMatrix = mat4<float>::scale2d(this->scale);
        mat4<float> rotationMatrix = mat4<float>::rotate2d(this->angle);
        mat4<float> translationMatrix = mat4<float>::translate2d(this->position);
        return scaleMatrix * rotationMatrix * translationMatrix;
    }

    void Rect::setPosition(const vec2<float> &p) {
        this->position = p;
    }

    void Rect::setRotation(const float &a) {
        this->angle = a;
    }

    void Rect::setScale(const vec2<float> &s) {
        this->scale = s;
    }

    vec2<float>& Rect::getDimensions() {
        return this->dimensions;
    }
}
