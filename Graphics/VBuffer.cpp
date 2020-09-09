#include "VBuffer.hpp"

namespace ga {
    VBuffer::VBuffer(const void* data, uint32_t bytes_Size, uint32_t usage) {
        GLCall(glGenBuffers(1, &this->n_BufferID));
        this->Bind();
        glBufferData(GL_ARRAY_BUFFER, bytes_Size, data, usage);
        this->Unbind();
    }

    VBuffer::~VBuffer() {
        GLCall(glDeleteBuffers(1, &this->n_BufferID));
    }

    VBuffer::VBuffer(VBuffer&& source) // Move constructor
        : n_BufferID(source.n_BufferID)
    {
        source.n_BufferID = 0;
    }

    void VBuffer::Bind() const {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->n_BufferID));
    }

    void VBuffer::Unbind() const {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
}
