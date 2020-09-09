#pragma once
#include <iostream>
#include <vector>
#include "VBuffer.hpp"
#include "IBuffer.hpp"
#include "VArray.hpp"
#include "VAttributes.hpp"
#include "Tex2d.hpp"
#include "vec3.hpp"
#include "vec2.hpp"
#include "mat4.hpp"

namespace ga {
    struct Vertex {
        vec3<float> position;
        vec3<float> normal;
        vec2<float> tex_coords;
    };

    class Mesh {
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<std::uint32_t> indices, std::vector<Tex2d> textures);
        void Bind() const;
        std::vector<std::uint32_t> getIndices() const;
        void printVertices() const;
        void printIndices() const;

        std::vector<Vertex>        vertices;
        std::vector<std::uint32_t> indices;
        std::vector<Tex2d>         textures;

        // opengl
        VBuffer vbuffer;
        IBuffer ibuffer;
        VAttributes attributes;
        VArray  varray;
    };
}
