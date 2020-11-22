#pragma once
#include <iostream>
#include <vector>
#include "VBuffer.hpp"
#include "IBuffer.hpp"
#include "VAttributes.hpp"
#include "VArray.hpp"
#include "vec3.hpp"
#include "mat4.hpp"

namespace vn {
    class Cube {
    public:
        Cube(float size);
        void Bind() const;
        mat4<float> getModel() const;
        std::vector<std::uint32_t> getIndices() const;
        void printVertices() const;
        [[nodiscard]] int getOpenGLDrawMode() const { return ogl_DrawMode; }
        void setOpenGLDrawMode(int mode) { this->ogl_DrawMode = mode; }

        // things
        std::vector<float> vertices;
        std::vector<std::uint32_t> indices;
        vec3<float> position{};
        vec3<float> scale{1.f, 1.f, 0.f};
        vec3<float> rotation{};

        // opengl
        VBuffer vbuffer;
        IBuffer ibuffer;
        VAttributes attributes;
        VArray varray;
        int ogl_DrawMode = GL_TRIANGLES;
    };
}


