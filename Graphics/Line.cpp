#include "Line.hpp"

namespace vn {
    Line::Line(const vec2f &v1, const vec2f &v2, const vec4f &color, float lineWidth) :
    buffer({
        v1.x, v1.y, color.r, color.g, color.b, color.a,
        v2.x, v2.y, color.r, color.g, color.b, color.a
    }),
    indices({
        0, 1
    }),
    vbuffer((const void*)buffer.data(), buffer.size() * sizeof(float)),
    ibuffer((const void*)indices.data(), indices.size() * sizeof(uint32_t)),
    m_LineWidth(lineWidth)
    {
        attributes.Insert<float>(2);
        attributes.Insert<float>(4);
        varray.addBuffer(vbuffer, attributes);
    }

    Line::Line(Line &&source)  noexcept :
    buffer(source.buffer),
    indices(source.indices),
    vbuffer(std::move(source.vbuffer)),
    ibuffer(std::move(source.ibuffer)),
    varray(std::move(source.varray))
    {
        m_LineWidth = source.m_LineWidth;
    }

    std::array<uint32_t, 2> Line::getIndices() const {
        return indices;
    }

    mat4f Line::getModel() const {
        return mat4f::identity();
    }

    void Line::Bind() const {
        varray.Bind();
        ibuffer.Bind();
    }

    float Line::getLineWidth() const {
        return this->m_LineWidth;
    }
}
