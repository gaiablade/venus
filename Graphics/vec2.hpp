#pragma once
#include <iostream>
#include <cmath>

namespace vn {
    template <typename T>
    class vec2 {
    public:
        T x{}, y{};
        vec2<T>() =default;
        vec2<T>(T x, T y) : x(x), y(y) {}
        explicit operator vec2<float>() const { return { this->x, this->y }; }
        vec2<T> unit() const;
        float angle() const;
    };

    template <typename T>
    vec2<T> vec2<T>::unit() const {
        T magnitude = std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2));
        return vec2<T>(this->x / magnitude, this->y / magnitude);
    }

    template <typename T>
    float vec2<T>::angle() const {
        return std::atan2(this->y, this->x);
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& out, vec2<T>& vec) {
        out << "[ " << vec.x << ", " << vec.y << " ]";
        return out;
    }

    typedef vec2<float> vec2f;
    typedef vec2<double> vec2d;
    typedef vec2<std::uint32_t> vec2u;
    typedef vec2<int> vec2i;
}
