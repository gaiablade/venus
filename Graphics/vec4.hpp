#pragma once
#include <iostream>

#define vec4f vec4<float>
#define vec4d vec4<double>
#define vec4i vec4<int>
#define vec4u vec4<std::uint32_t>

namespace ga {
    template <typename T>
    struct vec4 {
        union {
            struct {
                T x, y, z, w;
            };
            struct {
                T r, g, b, a;
            };
            T data[4];
        };
    };
}

