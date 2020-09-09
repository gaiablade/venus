#pragma once
#include <iostream>

namespace ga {
    template <typename T>
    class vec2 {
    public:
        T x, y;
        explicit operator vec2<float>() const { return { this->x, this->y }; }
    };

    typedef vec2<float> vec2f;
    typedef vec2<double> vec2d;
    typedef vec2<std::uint32_t> vec2u;
    typedef vec2<int> vec2i;
}
