#pragma once
#include <iostream>
#include <GL/glew.h>
#include "GLCall.hpp"

namespace ga {
    class IBuffer {
    public:
        IBuffer() = default;

        IBuffer(const void *data, const uint32_t &size_Bytes, uint32_t usage = GL_STATIC_DRAW);

        IBuffer(IBuffer&& source); // Copy constructor

        ~IBuffer();

        void Bind() const;

        void Unbind() const;

    private:
        uint32_t n_BufferID{};
    };
}

