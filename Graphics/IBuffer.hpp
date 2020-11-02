#pragma once
#include <iostream>
#include <GL/glew.h>
#include "GLCall.hpp"

namespace vn {
    class IBuffer {
    public:
        IBuffer();

        IBuffer(const void *data, const uint32_t &size_Bytes, uint32_t usage = GL_STATIC_DRAW);

        IBuffer(IBuffer&& source) noexcept; // Move constructor

        ~IBuffer();

        void Bind() const;

        void Unbind() const;

        void setData(const void* data, const uint32_t &size_Bytes, uint32_t usage = GL_STATIC_DRAW) const;

        // DEBUGGING:
        std::uint32_t DBG_GET_ID() const { return this->n_BufferID; }

    private:
        uint32_t n_BufferID{};
    };
}

