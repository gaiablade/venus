#pragma once
#include <iostream>
#include <vector>
#include "VBuffer.hpp"
#include "IBuffer.hpp"
#include "VAttributes.hpp"
#include "VArray.hpp"
#include "vec3.hpp"
#include "mat4.hpp"

namespace ga {
    class Cube {
    public:
        Cube(float size);
        void Bind() const;
        mat4<float> getModelView() const;
        std::vector<std::uint32_t> getIndices() const;
        void printVertices() const;

        // things
        std::vector<float> vertices;
        std::vector<std::uint32_t> indices;
        vec3<float> position{};
        vec3<float> scale{1.f, 1.f};
        vec3<float> rotation{};

        // opengl
        VBuffer vbuffer;
        IBuffer ibuffer;
        VAttributes attributes;
        VArray varray;
    };
}


