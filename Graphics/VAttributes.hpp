#pragma once
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include "GLCall.hpp"

namespace vn {
        struct VAttribute {
            uint32_t type;
            int count;
            uint8_t normalized;
            uint64_t size;
        };

        class VAttributes {
            public:
            VAttributes() = default;

            template <typename T>
            void Insert(const int32_t& count);
            void Build();

            std::vector<VAttribute>& getAttributes();
            private:
            std::vector<VAttribute> v_Attributes;
            int32_t n_Stride{};
        };
};

