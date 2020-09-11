#include "ColorRect.hpp"

namespace ga {
    ColorRect::ColorRect(const vec4f &color, const vec2f& dimensions) :
            indices({0, 2, 3, 0, 3, 1}),
            buffer({
                           -dimensions.x / 2.f, -dimensions.y / 2.f, color.r, color.g, color.b, color.a,
                           dimensions.x / 2.f, -dimensions.y / 2.f, color.r, color.g, color.b, color.a,
                           -dimensions.x / 2.f, dimensions.y / 2.f, color.r, color.g, color.b, color.a,
                           dimensions.x / 2.f, dimensions.y / 2.f, color.r, color.g, color.b, color.a
                   }),
            vbuffer(static_cast<const void *>(buffer.data()), buffer.size() * sizeof(float)),
            ibuffer(static_cast<const void *>(indices.data()), indices.size() * sizeof(uint32_t)),
            dimensions(dimensions)
    {
        this->attributes.Insert<float>(2);
        this->attributes.Insert<float>(4);
        this->varray.addBuffer(vbuffer, attributes);
    }

    ColorRect::ColorRect(ColorRect &&other) {
    }

    void ColorRect::Bind() const {
        this->varray.Bind();
        this->ibuffer.Bind();
    }

    IBuffer& ColorRect::getIBuffer() {
        return this->ibuffer;
    }

    std::array<uint32_t, 6> ColorRect::getIndices() const {
        return this->indices;
    }

    mat4f ColorRect::getModelView() const {
        mat4<float> scaleMatrix = mat4<float>::scale2d(this->scale);
        mat4<float> rotationMatrix = mat4<float>::rotate2d(this->angle);
        mat4<float> translationMatrix = mat4<float>::translate2d(this->position);
        return scaleMatrix * rotationMatrix * translationMatrix;
    }

    void ColorRect::setPosition(const vec2f &p) {
        this->position = p;
    }

    void ColorRect::setRotation(const float &a) {
        this->angle = a;
    }

    void ColorRect::setScale(const vec2f &s) {
        this->scale = s;
    }

    vec2f& ColorRect::getDimensions() {
        return this->dimensions;
    }

    vec2f ColorRect::getPosition() const {
        return this->position;
    }
}
