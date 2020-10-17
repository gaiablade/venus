#pragma once
#include <iostream>

namespace vn {
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

        ~vec4() = default;
    };

    typedef vec4<float> vec4f;
    typedef vec4<double> vec4d;
    typedef vec4<int> vec4i;
    typedef vec4<std::uint32_t> vec4u;
}
