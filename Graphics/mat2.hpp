#pragma once
#include <iostream>
#include <array>
#include <cmath>
#include <numbers>
#include "vec2.hpp"
#include "vec3.hpp"
#include "../System/Functions.hpp"

namespace num = std::numbers;

namespace ga {
    template <typename T>
    class mat2 {
    public:
        mat2();
        std::array<std::array<T, 2>, 2> data{};
        static constexpr mat2<T> rotation(const T& rot);
        vec2<T> operator* (const vec2<T>& other) const;
    };

    template <typename T>
    mat2<T>::mat2() = default;

    template <typename T>
    constexpr mat2<T> mat2<T>::rotation(const T &rot) {
        /*
        return mat2<T>{
            .data = {
                    {
                            std::array<T, 4>{
                                    std::cos(rot), std::sin(rot),
                                    -std::sin(rot), std::cos(rot)
                            }
                    }
            }
        };
         */
        mat2<T> mat;
        mat.data = {
                std::cos(rot), std::sin(rot),
                -std::sin(rot), std::cos(rot)
        };
        return mat;
    }

    template <typename T>
    vec2<T> mat2<T>::operator*(const vec2<T> &other) const {
        return vec2<T>{
            .x = this->data[0][0] * other.x + this->data[0][1] * other.y,
            .y = this->data[1][0] * other.x + this->data[1][1] * other.y
        };
    }

    typedef mat2<float> mat2f;
    typedef mat2<double> mat2d;
    typedef mat2<int> mat2i;
    typedef mat2<std::uint32_t> mat2u;
}
