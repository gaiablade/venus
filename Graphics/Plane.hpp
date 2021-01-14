#pragma once
#include "Mesh.hpp"
#include "Tex2d.hpp"

namespace vn {
    class Plane {
    public:
        Plane(const std::string& textureFile);
        Plane(Tex2d& texture);
        void GenInit();
        void Bind() const;
        std::vector<std::uint32_t> getIndices() const;
        mat4f getModel() const;

        [[nodiscard]] int getOpenGLDrawMode() const { return ogl_DrawMode; }
        void setOpenGLDrawMode(int mode) { this->ogl_DrawMode = mode; }

        vec3<float> position{ 0.f, 0.f, 0.f };
        vec3<float> scale{ 1.f, 1.f, 1.f };
        vec3<float> rotation{};

    private:
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        Tex2d* texture;
        VBuffer vbuffer;
        IBuffer ibuffer;
        VAttributes attributes;
        VArray varray;
        int ogl_DrawMode = GL_TRIANGLES;
    };
}


