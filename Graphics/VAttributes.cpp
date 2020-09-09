#include "VAttributes.hpp"

namespace ga {
    template <typename T>
    void VAttributes::Insert(const int32_t& count) {
        static_assert(sizeof(T) == -1);
    }

    template <>
    void VAttributes::Insert<float>(const int32_t& count) {
        this->n_Stride += sizeof(float) * count;
        this->v_Attributes.emplace_back(VAttribute{
                .type = GL_FLOAT, .count = count, .normalized = GL_FALSE, .size = count * sizeof(float)
        });
    }

    void VAttributes::Build() {
        uint32_t attr{0};
        int offset{0};
        for (auto& attribute : this->v_Attributes) {
            GLCall(glEnableVertexAttribArray(attr));
            GLCall(glVertexAttribPointer(attr, attribute.count, attribute.type, attribute.normalized, this->n_Stride, reinterpret_cast<void*>(offset)));
            attr++;
            offset += attribute.size;
        }
    }
}
