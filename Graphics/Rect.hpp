#pragma once
#include <iostream>
#include <array>
#include "VBuffer.hpp"
#include "VArray.hpp"
#include "VAttributes.hpp"
#include "IBuffer.hpp"
#include "vec2.hpp"
#include "mat4.hpp"

namespace ga {
    class Rect {
    public:
        Rect(const vec2<float> &dimensions);

        void Bind() const;

        IBuffer &getIBuffer();

        std::array<uint32_t, 6> getIndices() const;

        mat4<float> getModelView() const;

        // Set functions:
        void setPosition(const vec2<float> &p);

        void setRotation(const float &a);

        void setScale(const vec2<float> &s);

        // Get functions:
        vec2<float>& getDimensions();

    protected:
        // properties
        vec2<float> dimensions{};

        // transforms
        vec2<float> position{0.f, 0.f};
        vec2<float> scale{1.f, 1.f};
        float angle{0.f};

        // opengl stuff
        std::array<uint32_t, 6> indices;
        std::array<float, 20> buffer;
        VBuffer vbuffer;
        IBuffer ibuffer;
        VAttributes attributes;
        VArray varray;
    };
}

