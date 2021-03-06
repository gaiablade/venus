#pragma once
#include <iostream>
#include <array>
#include "VBuffer.hpp"
#include "VArray.hpp"
#include "VAttributes.hpp"
#include "IBuffer.hpp"
#include "vec2.hpp"
#include "mat4.hpp"

namespace vn {
    const int numPoints = 1000;

    class Circle {
    public:
        Circle(const float &radius);

        void Bind() const;

        IBuffer &getIBuffer();

        std::array<uint32_t, numPoints + 2> getIndices() const;

        mat4<float> getModel() const;

        // Set functions:
        void setPosition(const vec2<float> &p);

        void setRotation(const float &a);

        void setScale(const vec2<float> &s);

        [[nodiscard]] int getOpenGLDrawMode() const { return ogl_DrawMode; }

    private:
        // properties
        vec2<float> position{0.f, 0.f};
        vec2<float> scale{1.f, 1.f};
        float angle{0.f};

        // opengl stuff
        std::array<uint32_t, numPoints + 2> indices;
        std::array<float, (numPoints + 1) * 5> buffer;
        VBuffer vbuffer{};
        IBuffer ibuffer{};
        VAttributes attributes;
        VArray varray;
        int ogl_DrawMode = GL_TRIANGLE_FAN;
    };
}

