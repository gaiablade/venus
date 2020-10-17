#pragma once
#include <iostream>
#include <array>
#include "mat4.hpp"
#include "VArray.hpp"
#include "IBuffer.hpp"

namespace vn {
    template <class Vertex, size_t numVertices, size_t numIndices>
    class AbstractShape {
    public:
        AbstractShape(const std::array<Vertex, numVertices>& vertices, const std::array<uint32_t, numIndices>& indices);
        mat4f getModelView() const;
        std::array<uint32_t, numIndices> getIndices() const;
        void Bind() const;
    private:
        std::array<Vertex, numVertices> vertices;
        std::array<uint32_t, numIndices> indices;
        VBuffer vbuffer;
        IBuffer ibuffer;
        VArray varray;
        VAttributes attributes;
    };

    template <class Vertex, size_t numVertices, size_t numIndices>
    AbstractShape<Vertex, numVertices, numIndices>::AbstractShape(const std::array<Vertex, numVertices>& vertices, const std::array<uint32_t, numIndices>& indices)
            : vertices(vertices), indices(indices),
              vbuffer((const void*)this->vertices.data(), sizeof(Vertex) * this->vertices.size()),
              ibuffer((const void*)this->indices.data(), sizeof(uint32_t) * this->indices.size())
    {
        this->attributes.template Insert<float>(2);
        this->attributes.template Insert<float>(4);
        this->varray.addBuffer(this->vbuffer, this->attributes);
    }

    template <class Vertex, size_t numVertices, size_t numIndices>
    mat4f AbstractShape<Vertex, numVertices, numIndices>::getModelView() const {
        mat4f matrix = mat4f::identity();
        return matrix;
    }

    template <class Vertex, size_t numVertices, size_t numIndices>
    std::array<uint32_t, numIndices> AbstractShape<Vertex, numVertices, numIndices>::getIndices() const {
        return this->indices;
    }

    template <class Vertex, size_t numVertices, size_t numIndices>
    void AbstractShape<Vertex, numVertices, numIndices>::Bind() const {
        this->varray.Bind();
        this->ibuffer.Bind();
    }
};
