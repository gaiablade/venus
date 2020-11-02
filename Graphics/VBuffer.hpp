#pragma once
#include <iostream>
#include <GL/glew.h>
#include "GLCall.hpp"

namespace vn {
    struct Attribute {
        uint32_t n_Type;
        uint32_t n_Size;
    };

    class VBuffer {
    public:
        VBuffer();
        VBuffer(const void* data, uint32_t bytes_Size, uint32_t usage = GL_STATIC_DRAW);
        VBuffer(VBuffer&& source) noexcept ; // move constructor
        ~VBuffer();
        void Bind() const;
        void Unbind() const;

        void setData(const void* data, uint32_t bytes_Size, uint32_t usage = GL_STATIC_DRAW);

        // Debugging:
        uint32_t getID() const { return this->n_BufferID; }
    private:
        uint32_t n_BufferID{};
    };
}

