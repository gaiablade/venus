#pragma once
#include <array>
#include "IBuffer.hpp"
#include "mat4.hpp"
#include "VArray.hpp"
#include "vec2.hpp"
#include "vec4.hpp"

namespace vn {
    class Line {
    public:
        Line(const vec2f& v1, const vec2f& v2, const vec4f& color, float lineWidth = 1.0f);
        Line(Line&& source) noexcept;
        [[nodiscard]] std::array<uint32_t, 2> getIndices() const;
        [[nodiscard]] mat4f getModel() const;
        void Bind() const;
        [[nodiscard]] float getLineWidth() const;
        [[nodiscard]] int getOpenGLDrawMode() const { return ogl_DrawMode; }
        void setOpenGLDrawMode(int mode) { this->ogl_DrawMode = mode; }
    private:
        std::array<float, 12> buffer;
        std::array<uint32_t, 2> indices;
        float m_LineWidth;

        // OpenGL stuff:
        VBuffer vbuffer;
        IBuffer ibuffer;
        VAttributes attributes;
        VArray varray;
        int ogl_DrawMode = GL_LINES;
    };
}
