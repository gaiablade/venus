#ifndef GLTEST_VEC3_HPP
#define GLTEST_VEC3_HPP

#include <cmath>
#include <numbers>

namespace num = std::numbers;

namespace vn {
    template <typename T>
    struct vec3 {
        union {
            T data[3];
            struct {
                T x, y, z;
            };
        };

        vec3() =default;

        vec3(T x, T y, T z) : x(x), y(y), z(z) {}

        T& operator[] (int index) { return data[index]; }

        static vec3<T> degrees(const vec3<T>& vec);
    };

    template <typename T>
    vec3<T> vec3<T>::degrees(const vec3<T> &vec) {
        return vec3<T>{
            vec.x * num::pi / 180.f, vec.y * num::pi / 180.f, vec.z * num::pi / 180.f
        };
    }

    typedef vec3<float> vec3f;
    typedef vec3<double> vec3d;
    typedef vec3<int> vec3i;
    typedef vec3<std::uint32_t> vec3u;
}

#endif //GLTEST_VEC3_HPP
