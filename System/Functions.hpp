#pragma once
#include <numbers>

namespace num = std::numbers;

namespace ga {
    template <typename T>
    static T degrees(const T& in_degrees) {
        return in_degrees * num::pi / 180.f;
    }
}