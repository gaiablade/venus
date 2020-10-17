#pragma once
#include <iostream>
#include <array>
#include "VBuffer.hpp"
#include "VArray.hpp"
#include "VAttributes.hpp"
#include "IBuffer.hpp"
#include "vec2.hpp"
#include "mat4.hpp"
#include "vec4.hpp"

namespace vn {
    class ColorRect {
    public:
        ColorRect(const vec4f& color, const vec2f& dimensions);

        ColorRect(ColorRect&& other) noexcept ;

        void Bind() const;

        IBuffer &getIBuffer();

        std::array<uint32_t, 6> getIndices() const;

        mat4f getModelView() const;

        // Set functions:
        void setPosition(const vec2f &p);

        void setRotation(const float &a);

        void setScale(const vec2f &s);

        // Get functions:
        vec2f& getDimensions();

        vec2f getPosition() const;

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

        // opengl stuff
        std::array<uint32_t, 6> indices;
        std::array<float, 24> buffer;
        VBuffer vbuffer;
        IBuffer ibuffer;
        VAttributes attributes;
        VArray varray;
    };
}
