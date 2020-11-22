#include "Cube.hpp"

namespace vn {
    Cube::Cube(float size)
        : vertices({
            -size, -size,  size,
            size, -size,  size,
            size,  size,  size,
            -size,  size,  size,
            -size, -size, -size,
            size, -size, -size,
            size,  size, -size,
            -size,  size, -size
        }),
        indices({
            0, 1, 2,
            2, 3, 0,
            1, 5, 6,
            6, 2, 1,
            7, 6, 5,
            5, 4, 7,
            4, 0, 3,
            3, 7, 4,
            4, 5, 1,
            1, 0, 4,
            3, 2, 6,
            6, 7, 3
        }),
        vbuffer((const void*)vertices.data(), vertices.size() * sizeof(float)),
        ibuffer((const void*)indices.data(), indices.size() * sizeof(std::uint32_t))
    {
        attributes.Insert<float>(3);
        varray.addBuffer(vbuffer, attributes);
    }

    void Cube::Bind() const {
        this->varray.Bind();
        this->ibuffer.Bind();
    }

    mat4<float> Cube::getModel() const {
        mat4<float> transformation = mat4<float>::rotate3d(this->rotation) * mat4<float>::scale3d(this->scale) * mat4<float>::translate3d(this->position);
        return transformation;
    }

    std::vector<std::uint32_t> Cube::getIndices() const {
        return this->indices;
    }

    void Cube::printVertices() const {
        std::cout << "buffer ID: " << this->vbuffer.getID() << '\n';
        std::cout << "array ID: " << this->varray.getID() << '\n';
        std::cout << "[\n";
        for (int i = 0; i < this->vertices.size() / 3; i++) {
            std::cout << this->vertices[0 + 3 * i] << ' ' << this->vertices[1 + 3 * i] << ' ' << this->vertices[2 + 3 * i] << '\n';
        }
        std::cout << "]\n";
    }
}