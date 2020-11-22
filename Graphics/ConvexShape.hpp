#pragma once
#include <iostream>
#include <array>
#include <fmt/core.h>
#include <utility>
#include "mat4.hpp"
#include "VArray.hpp"
#include "IBuffer.hpp"

namespace vn {
    template<class Vertex, size_t numVertices>
    class ConvexShape {
    public:
        ConvexShape(const std::array<Vertex, numVertices> &vertices);

        int calculateIndices();

        [[nodiscard]] vn::mat4f getModel() const;

        std::array<uint32_t, 3 * (numVertices - 2)> getIndices() const;

        void Bind() const;

        [[nodiscard]] int getOpenGLDrawMode() const { return ogl_DrawMode; }

        void setOpenGLDrawMode(int mode) { this->ogl_DrawMode = mode; }

    private:
        std::array<Vertex, numVertices> vertices;
        int throwaway;
        // number of indices = 3 * (numVertices - 2)
        std::array<uint32_t, 3 * (numVertices - 2)> indices;
        vn::VBuffer vbuffer;
        vn::IBuffer ibuffer;
        vn::VArray varray;
        vn::VAttributes attributes;
        int ogl_DrawMode = GL_TRIANGLES;
    };

    template<class Vertex, size_t numVertices>
    ConvexShape<Vertex, numVertices>::ConvexShape(const std::array<Vertex, numVertices> &vertices)
            : vertices(vertices), throwaway(calculateIndices()),
              vbuffer((const void *) this->vertices.data(), sizeof(Vertex) * vertices.size()),
              ibuffer((const void *) this->indices.data(), indices.size() * sizeof(uint32_t)),
              attributes() {
        static_assert(numVertices >= 2);

        this->attributes.template Insert<float>(2);
        this->attributes.template Insert<float>(4);
        varray.addBuffer(this->vbuffer, this->attributes);
    }

    template<class Vertex, size_t numVertices>
    int ConvexShape<Vertex, numVertices>::calculateIndices() {
        int numIndicePairs = numVertices - 2;
        for (size_t i = 0; i < numIndicePairs; i++) {
            indices[i * 3] = 0;
            indices[i * 3 + 1] = i + 1;
            indices[i * 3 + 2] = i + 2;
        }
        return 1;
    }

    template<class Vertex, size_t numVertices>
    vn::mat4f ConvexShape<Vertex, numVertices>::getModel() const {
        vn::mat4f matrix = vn::mat4f::identity();
        return matrix;
    }

    template<class Vertex, size_t numVertices>
    std::array<uint32_t, 3 * (numVertices - 2)> ConvexShape<Vertex, numVertices>::getIndices() const {
        return this->indices;
    }

    template<class Vertex, size_t numVertices>
    void ConvexShape<Vertex, numVertices>::Bind() const {
        varray.Bind();
        ibuffer.Bind();
    }
}
