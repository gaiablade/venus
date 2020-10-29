#pragma once
#include <iostream>
#include <array>
#include "VBuffer.hpp"
#include "VArray.hpp"
#include "VAttributes.hpp"
#include "IBuffer.hpp"
#include "vec2.hpp"
#include "mat4.hpp"
#include "Tex2d.hpp"

namespace vn {
    class Sprite {
    public:
        Sprite(Tex2d& texture);

        Sprite(Sprite&& other);

        void Bind() const;

        IBuffer &getIBuffer();

        std::array<uint32_t, 6> getIndices() const;

        mat4<float> getModelView() const;

        // Set functions:
        void setPosition(const vec2<float> &p);

        void setRotation(const float &a);

        void setScale(const vec2<float> &s);

        void setTexRectangle(float l, float t, float w, float h);

        // Get functions:
        vec2<float>& getDimensions();

        vec2<float> getPosition() const;

        vec2f getScale() const;

        void setFlipped(bool flipped);

    private:
        // properties
        vec2<float> dimensions{};

        // transformations
        vec2<float> position{0.f, 0.f};
        vec2<float> scale{1.f, 1.f};
        float angle{0.f};
        bool flipped{false};

        // opengl stuff
        std::array<uint32_t, 6> indices;
        std::array<float, 16> buffer;
        VBuffer vbuffer;
        IBuffer ibuffer;
        VAttributes attributes;
        VArray varray;
        Tex2d* texture{};
    };
}

