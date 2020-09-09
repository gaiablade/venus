#include "Mesh.hpp"

#include <utility>

namespace ga {
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<std::uint32_t> indices, std::vector<Tex2d> textures) :
        vertices(std::move(vertices)), indices(std::move(indices)), textures(std::move(textures)),
        vbuffer((const void*)this->vertices.data(), this->vertices.size() * sizeof(Vertex)),
        ibuffer((const void*)this->indices.data(), this->indices.size() * sizeof(std::uint32_t))
    {
        this->attributes.Insert<float>(3); // position
        this->attributes.Insert<float>(3); // normals
        this->attributes.Insert<float>(2); // tex_coords
        this->varray.addBuffer(this->vbuffer, this->attributes);
    }

    void Mesh::Bind() const {
        this->varray.Bind();
        this->ibuffer.Bind();
        if (!this->textures.empty()) {
            this->textures[0].Bind();
        }
        else {
            glActiveTexture(GL_TEXTURE0 + 0);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

    }

    std::vector<std::uint32_t> Mesh::getIndices() const {
        return this->indices;
    }

    void Mesh::printVertices() const {
        std::cout << "buffer ID: " << this->vbuffer.getID() << '\n';
        std::cout << "array ID: " << this->varray.getID() << '\n';
        std::cout << "[\n";
        for (auto& vertex : this->vertices) {
            std::cout << '\t' << vertex.position.x << ' ' << vertex.position.y << ' ' << vertex.position.z << '\n';
            /*
            std::cout << '\t' << vertex.position.x << ' ' << vertex.position.y << ' ' << vertex.position.z << ' ' << vertex.normal.x
                << ' ' << vertex.normal.y << ' ' << vertex.normal.z << ' ' << vertex.tex_coords.x << ' ' << vertex.tex_coords.y << '\n';
                */
        }
        std::cout << "]\n";
    }

    void Mesh::printIndices() const {
        std::cout << "[\n";
        for (auto& index : this->indices) {
            std::cout << '\t' << index << '\n';
        }
        std::cout << "]\n";
    }
}
