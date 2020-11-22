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
        struct v {
            vec2f dimensions;
            vec2f texCoords;

            v() = default;
            v(vec2f dimensions, vec2f texCoords) : dimensions(dimensions), texCoords(texCoords)
            {
            }
        };
    public:
        Sprite(Tex2d& texture);

        Sprite(Sprite&& other);

        void Bind() const;

        IBuffer &getIBuffer();

        std::array<uint32_t, 6> getIndices() const;

        mat4<float> getModel() const;

        // Set functions:
        void setPosition(const vec2<float> &p);

        void setRotation(const float &a);

        float getRotation() const;

        void setScale(const vec2<float> &s);

        void setSize(const vn::vec2f& size);

        void setTexRectangle(float l, float t, float w, float h);

        // Get functions:
        vec2<float>& getDimensions();

        vec2f getScaledDimensions() const;

        vec2f getPosition() const;

        vec2f getScale() const;

        void setFlipped(bool flipped);

        [[nodiscard]] int getOpenGLDrawMode() const { return ogl_DrawMode; }

        void setOpenGLDrawMode(int mode) { this->ogl_DrawMode = mode; }

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
        //std::array<float, 16> buffer;
        std::array<v, 4> buffer;
        VBuffer vbuffer;
        IBuffer ibuffer;
        VAttributes attributes;
        VArray varray;
        Tex2d* texture{};
        int ogl_DrawMode = GL_TRIANGLES;
    };
}

