#include "BorderRect.hpp"

namespace vn {
    BorderRect::BorderRect(const vec4f &color, const vec2f& dimensions, int lineWidth) :
            indices({0, 1, 3, 2}),
            buffer({
                           -dimensions.x / 2.f, -dimensions.y / 2.f, color.r, color.g, color.b, color.a,
                           dimensions.x / 2.f, -dimensions.y / 2.f, color.r, color.g, color.b, color.a,
                           -dimensions.x / 2.f, dimensions.y / 2.f, color.r, color.g, color.b, color.a,
                           dimensions.x / 2.f, dimensions.y / 2.f, color.r, color.g, color.b, color.a
                   }),
            vbuffer(static_cast<const void *>(buffer.data()), buffer.size() * sizeof(float)),
            ibuffer(static_cast<const void *>(indices.data()), indices.size() * sizeof(uint32_t)),
            dimensions(dimensions),
            m_LineWidth(lineWidth)
    {
        this->attributes.Insert<float>(2);
        this->attributes.Insert<float>(4);
        this->varray.addBuffer(vbuffer, attributes);
    }

    BorderRect::BorderRect(BorderRect &&other) noexcept :
            color(other.color), indices(other.indices), buffer(other.buffer), ibuffer(std::move(other.ibuffer)),
            vbuffer(std::move(other.vbuffer)), dimensions(other.dimensions), position(other.position),
            varray(std::move(other.varray))
    {
    }

    void BorderRect::Bind() const {
        this->varray.Bind();
        this->ibuffer.Bind();
        glLineWidth(m_LineWidth);
    }

    IBuffer& BorderRect::getIBuffer() {
        return this->ibuffer;
    }

    std::array<uint32_t, 4> BorderRect::getIndices() const {
        return this->indices;
    }

    mat4f BorderRect::getModel() const {
        mat4<float> scaleMatrix = mat4<float>::scale2d(this->scale);
        mat4<float> rotationMatrix = mat4<float>::rotate2d(this->angle);
        mat4<float> translationMatrix = mat4<float>::translate2d(this->position);
        return scaleMatrix * rotationMatrix * translationMatrix;
    }

    void BorderRect::setPosition(const vec2f &p) {
        this->position = p;
    }

    void BorderRect::setRotation(const float &a) {
        this->angle = a;
    }

    void BorderRect::setScale(const vec2f &s) {
        this->scale = s;
    }

    vec2f& BorderRect::getDimensions() {
        return this->dimensions;
    }

    vec2f BorderRect::getPosition() const {
        return this->position;
    }

    void BorderRect::setLineWidth(int width) {
        m_LineWidth = width;
    }
}
