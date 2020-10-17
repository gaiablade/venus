#include "IBuffer.hpp"

namespace vn {
    IBuffer::IBuffer(const void *data, const uint32_t &size_Bytes, uint32_t usage) {
        GLCall(glGenBuffers(1, &this->n_BufferID));
        this->Bind();
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_Bytes, data, usage));
    }

    IBuffer::IBuffer(IBuffer &&source) noexcept // Move constructor
        : n_BufferID(source.n_BufferID)
    {
        source.n_BufferID = 0;
    }

    IBuffer::~IBuffer() {
        GLCall(glDeleteBuffers(1, &this->n_BufferID));
    }

    void IBuffer::Bind() const {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->n_BufferID));
    }

    void IBuffer::Unbind() const {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }
}