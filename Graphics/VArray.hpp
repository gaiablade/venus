#pragma once
#include "VBuffer.hpp"
#include "VAttributes.hpp"

namespace vn {
    class VArray {
    public:
        VArray();
        VArray(VArray&& other);
        void addBuffer(VBuffer& buffer, VAttributes& attributes);
        void Bind() const;
        static void Unbind() ;

        // Debugging
        uint32_t getID() const { return this->n_VArrayID; }
    private:
        uint32_t n_VArrayID{};
    };
}

