#ifndef GLTEST_VEC3_HPP
#define GLTEST_VEC3_HPP

#include <cmath>
#include <numbers>

namespace num = std::numbers;

namespace ga {
    template <typename T>
    struct vec3 {
        union {
            T data[3];
            struct {
                T x, y, z;
            };
        };
        T& operator[] (int index) { return data[index]; }

        static vec3<T> degrees(const vec3<T>& vec);
    };

    template <typename T>
    vec3<T> vec3<T>::degrees(const vec3<T> &vec) {
        return vec3<T>{
            vec.x * num::pi / 180.f, vec.y * num::pi / 180.f, vec.z * num::pi / 180.f
        };
    }
}

#endif //GLTEST_VEC3_HPP
