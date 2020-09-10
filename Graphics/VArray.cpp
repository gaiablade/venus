#include "VArray.hpp"

namespace ga {
    VArray::VArray() {
        GLCall(glGenVertexArrays(1, &this->n_VArrayID));
    }

    VArray::VArray(VArray&& other) : n_VArrayID(other.n_VArrayID) {
        other.n_VArrayID = 0;
    }

    void VArray::addBuffer(VBuffer &buffer, VAttributes &attributes) {
        this->Bind();
        buffer.Bind();
        attributes.Build();
        VArray::Unbind();
    }

    void VArray::Bind() const {
        GLCall(glBindVertexArray(this->n_VArrayID));
    }

    void VArray::Unbind() {
        GLCall(glBindVertexArray(0));
    }
}