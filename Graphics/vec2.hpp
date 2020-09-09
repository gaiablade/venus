#pragma once

#define vec2f vec2<float>
#define vec2d vec2<double>
#define vec2i vec2<int>
#define vec2u vec2<std::uint32_t>

namespace ga {
    template <typename T>
    class vec2 {
    public:
        T x, y;
        explicit operator vec2<float>() const { return { this->x, this->y }; }
    };
}


