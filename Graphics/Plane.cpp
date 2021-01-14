#include "Plane.hpp"

namespace vn {

    Plane::Plane(const std::string &textureFile) :
    vertices({
        Vertex(vec3f(-1, 0, 1), vec3f(0, 1, 0), vec2f(0, 0)),
        Vertex(vec3f(1, 0, 1), vec3f(0, 1, 0), vec2f(1, 0)),
        Vertex(vec3f(-1, 0, -1), vec3f(0, 1, 0), vec2f(0, 1)),
        Vertex(vec3f(1, 0, -1), vec3f(0, 1, 0), vec2f(1, 1))
    }),
    indices({0, 1, 2, 1, 2, 3}),
    texture(new Tex2d(textureFile)),
    vbuffer((const void*)vertices.data(), sizeof(Vertex) * vertices.size()),
    ibuffer((const void*)indices.data(), sizeof(uint32_t) * indices.size())
    {
        GenInit();
    }

    Plane::Plane(Tex2d& texture) :
    vertices({
        Vertex(vec3f(-1, 0, 1), vec3f(0, 1, 0), vec2f(0, 0)),
        Vertex(vec3f(1, 0, 1), vec3f(0, 1, 0), vec2f(1, 0)),
        Vertex(vec3f(-1, 0, -1), vec3f(0, 1, 0), vec2f(0, 1)),
        Vertex(vec3f(1, 0, -1), vec3f(0, 1, 0), vec2f(1, 1))
    }),
    indices({0, 1, 2, 1, 2, 3}),
    texture(&texture),
    vbuffer((const void*)vertices.data(), sizeof(Vertex) * vertices.size()),
    ibuffer((const void*)indices.data(), sizeof(uint32_t) * indices.size())
    {
        GenInit();
    }

    void Plane::GenInit() {
        this->attributes.Insert<float>(3); // position
        this->attributes.Insert<float>(3); // normals
        this->attributes.Insert<float>(2); // tex_coords
        this->varray.addBuffer(this->vbuffer, this->attributes);
    }

    void Plane::Bind() const {
        this->varray.Bind();
        this->ibuffer.Bind();
        this->texture->Bind();
    }

    std::vector<std::uint32_t> Plane::getIndices() const {
        return this->indices;
    }

    mat4f Plane::getModel() const {
        mat4<float> transformation = mat4<float>::rotate3d(this->rotation) * mat4<float>::scale3d(this->scale) * mat4<float>::translate3d(this->position);
        return transformation;
    }
}
