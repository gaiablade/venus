#pragma once
namespace ga {
    template <typename T>
    class vec2 {
    public:
        T x, y;
        explicit operator vec2<float>() const { return { this->x, this->y }; }
    };
}


