#pragma once
#include <array>
#include <iostream>
#include "IBuffer.hpp"
#include "VArray.hpp"
#include "mat4.hpp"
#include "vec2.hpp"
#include "vec4.hpp"

namespace vn {
    class BorderRect {
    public:
        BorderRect(const vec4f& color, const vec2f& dimensions, int lineWidth = 1.f);

        BorderRect(BorderRect&& other) noexcept ;

        void Bind() const;

        IBuffer &getIBuffer();

        std::array<uint32_t, 4> getIndices() const;

        mat4f getModel() const;

        // Set functions:
        void setPosition(const vec2f &p);

        void setRotation(const float &a);

        void setScale(const vec2f &s);

        // Get functions:
        vec2f& getDimensions();

        vec2f getPosition() const;

        void setLineWidth(int width);

        [[nodiscard]] int getOpenGLDrawMode() const { return ogl_DrawMode; }

        void setOpenGLDrawMode(int mode) { this->ogl_DrawMode = mode; }

        // Debugging:
        VBuffer& DBG_GET_VBUFFER() { return this->vbuffer; }
        VArray& DBG_GET_VARRAY() { return this->varray; }

    private:
        // properties
        vec2f dimensions{};
        vec4f color;

        // transformations
        vec2f position{0.f, 0.f};
        vec2f scale{1.f, 1.f};
        float angle{0.f};
        uint32_t m_LineWidth = 1.f;

        // opengl stuff
        std::array<uint32_t, 4> indices;
        std::array<float, 24> buffer;
        VBuffer vbuffer;
        IBuffer ibuffer;
        VAttributes attributes;
        VArray varray;
        int ogl_DrawMode = GL_LINE_LOOP;
    };
};
