#pragma once
#include <iostream>
#include <array>
#include <cmath>
#include <numbers>
#include "vec2.hpp"
#include "vec3.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace num = std::numbers;

namespace vn {
    enum class CON {
        ORTHO = 0
    };

    struct orthoData {
        float l, r, t, b;
        float n = 0.f, f = 100.f;
        float width, height;
        orthoData(float l, float r, float t, float b, float n = 0.f, float f = 100.f)
            : l(l), r(r), t(t), b(b), n(n), f(f), width(r - l), height(b - t)
        {
        }
        orthoData() =default;
    };

    struct perspData {
        float near, far, aspect, fov;
        perspData(float near, float far, float aspect, float fov) : near(near), far(far), aspect(aspect), fov(fov) {}
    };

    template<typename T>
    class mat4 {
    public:
        std::array<std::array<T, 4>, 4> data{};

        void print() const;

        static constexpr mat4<T> identity();

        static constexpr mat4<T> ortho2d(const orthoData &);

        static constexpr mat4<T> ortho3d(const orthoData &);

        static constexpr mat4<T> perspective(const perspData &);

        static mat4<T> rotate2d(const float &angle);

        static mat4<T> rotate3d(const vec3<float> &rotation);

        static constexpr mat4<T> translate2d(const vec2<float> &movement);

        static constexpr mat4<T> translate3d(const vec3<float> &movement);

        static constexpr mat4<T> scale2d(const vec2<float> &factor);

        static constexpr mat4<T> scale3d(const vec3<float> &factor);

        vec2<T> operator*(const vec2<T> &vec);

        vec3<T> operator*(const vec3<T> &vec);

        constexpr mat4<T> operator*(const mat4<T> &mat) const;

        constexpr mat4<T> multiply(const mat4<T> &mat) const;

        const std::array<T, 4> &operator[](int index) const { return this->data[index]; }

        std::array<T, 4> &operator[](int index) { return this->data[index]; }

        vec2<T> getPosition() const;
    };

    template<typename T>
    void mat4<T>::print() const {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << this->data[j][i] << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    template<typename T>
    constexpr mat4<T> mat4<T>::identity() {
        return mat4<T>{
                .data = {
                        {
                                {1, 0, 0, 0},
                                {0, 1, 0, 0},
                                {0, 0, 1, 0},
                                {0, 0, 0, 1}
                        }
                }
        };
    }

    template<typename T>
    constexpr mat4<T> mat4<T>::ortho2d(const orthoData &d) {
        return mat4<T>{
                .data = {
                        {
                                {2 / (d.r - d.l), 0, 0, 0},
                                {0, 2 / (d.t - d.b), 0, 0},
                                {0, 0, 1, 0},
                                {-((d.r + d.l) / (d.r - d.l)), -((d.t + d.b) / (d.t - d.b)), 0, 1}

                        }
                }
        };
    }

    template <typename T>
    constexpr mat4<T> mat4<T>::ortho3d(const orthoData &d) {
        return mat4<T>{
                .data = {
                        {
                                {2 / (d.r - d.l), 0, 0, 0},
                                {0, 2 / (d.t - d.b), 0, 0},
                                {0, 0, -2 / (d.f - d.n), 0},
                                {-((d.r + d.l) / (d.r - d.l)), -((d.t + d.b) / (d.t - d.b)), -((d.f + d.n) / (d.f - d.n)), 1}

                        }
                }
        };
    }

    template <typename T>
    constexpr mat4<T> mat4<T>::perspective(const perspData &d) {
        const float fovh = std::tan(d.fov / 2.f);
        return {
            .data = {
                    {
                            { 1 / (d.aspect * fovh), 0, 0, 0 },
                            { 0, 1 / fovh, 0, 0 },
                            { 0, 0, -(d.far + d.near)/(d.far - d.near), (-2 * d.far * d.near)/(d.far - d.near) },
                            { 0, 0, -1, 0 }
                    }
            }
        };
        /*
        const auto f = 1.f / std::tan((30.f * num::pi / 180.f) / 2);
        //const auto f = std::tan(num::pi * 0.5 - 0.5 * (45.f * num::pi / 180.f));
        const auto nf = 1.f / (d.n - d.f);
        return mat4<T>{
            .data = {
                    {
                            { f / (1280.f / 720.f), 0, 0, 0 },
                            { 0, f, 0, 0 },
                            { 0, 0, (d.f + d.n) * nf, -1 },
                            { 0, 0, (2 * d.n * d.f) * nf, 0}
                            */
                        /*
                            { f / (1280.f / 720.f), 0, 0, 0 },
                            { 0, f, 0, 0 },
                            { 0, 0, (d.f + d.n) * nf, (2 * d.n * d.f) * nf },
                            { 0, 0, -1, 0}
                            */
                        /*
                    }
            }
        };
                         */
    }

    template<typename T>
    mat4<T> mat4<T>::rotate2d(const float &angle) {
        const float a = angle * M_PI / 180.f;
        return mat4<T>{
                .data = {
                        {
                                {std::cos(a), std::sin(a), 0, 0},
                                {-std::sin(a), std::cos(a), 0, 0},
                                {0, 0, 1, 0},
                                {0, 0, 0, 1}
                        }
                }
        };
    }

    template <typename T>
    mat4<T> mat4<T>::rotate3d(const vec3<float> &rotation) {
        const mat4<T> iden = mat4<T>::identity();
        const mat4<T> rotX = {
                .data = {
                        {
                                { 1, 0, 0, 0 },
                                { 0, std::cos(rotation.x), -std::sin(rotation.x), 0 },
                                { 0, std::sin(rotation.x),  std::cos(rotation.x), 0 },
                                { 0, 0, 0, 1 }
                        }
                }
        };
        const mat4<T> rotY = {
                .data = {
                        {
                                { std::cos(rotation.y), 0, std::sin(rotation.y), 0 },
                                { 0, 1, 0, 0 },
                                { -std::sin(rotation.y), 0, std::cos(rotation.y), 0 },
                                { 0, 0, 0, 1 }
                        }
                }
        };
        const mat4<T> rotZ = {
                .data = {
                        {
                                { std::cos(rotation.z), -std::sin(rotation.z), 0, 0 },
                                { std::sin(rotation.z), std::cos(rotation.z), 0, 0 },
                                { 0, 0, 1, 0 },
                                { 0, 0, 0, 1 }
                        }
                }
        };
        return iden * rotX * rotY * rotZ;
    }

    template<typename T>
    constexpr mat4<T> mat4<T>::translate2d(const vec2<float> &movement) {
        return mat4<T>{
                .data = {
                        {
                                {1, 0, 0, 0},
                                {0, 1, 0, 0},
                                {0, 0, 1, 0},
                                {movement.x, movement.y, 0, 1}
                        }
                }
        };
    }

    template <typename T>
    constexpr mat4<T> mat4<T>::translate3d(const vec3<float> &movement) {
        return mat4<T>{
                .data = {
                        {
                                {1, 0, 0, 0},
                                {0, 1, 0, 0},
                                {0, 0, 1, 0},
                                {movement.x, movement.y, movement.z, 1}
                        }
                }
        };
    }

    template<typename T>
    constexpr mat4<T> mat4<T>::scale2d(const vec2<float> &factor) {
        return mat4<T>{
                .data = {
                        {
                                {factor.x, 0, 0, 0},
                                {0, factor.y, 0, 0},
                                {0, 0, 1, 0},
                                {0, 0, 0, 1}
                        }
                }
        };
    }

    template <typename T>
    constexpr mat4<T> mat4<T>::scale3d(const vec3<float> &factor) {
        return mat4<T>{
                .data = {
                        {
                                {factor.x, 0, 0, 0},
                                {0, factor.y, 0, 0},
                                {0, 0, factor.z, 0},
                                {0, 0, 0, 1}
                        }
                }
        };
    }

    template<typename T>
    vec2<T> mat4<T>::operator*(const vec2<T> &vec) {
        return vec2<T>{
                .x = this->data[0][0] * vec.x + this->data[0][3],
                .y = this->data[1][1] * vec.y + this->data[1][3]
        };
    }

    template<typename T>
    vec3<T> mat4<T>::operator*(const vec3<T> &vec) {
        /*
        return vec3<T>{
                .x = this->data[0][0] * vec.x + this->data[0][3],
                .y = this->data[1][1] * vec.y + this->data[1][3],
                .z = this->data[2][2] * vec.z + this->data[2][3]
        };
         */
        /*
        return vec3<T>{
                this->data[0][0] * vec.x + this->data[0][3],
                this->data[1][1] * vec.y + this->data[1][3],
                this->data[2][2] * vec.z + this->data[2][3]
        };
         */
        return vec3<T>{
            this->data[0][0] * vec.x + this->data[0][1] * vec.y + this->data[0][2] * vec.z + this->data[0][3],
            this->data[1][0] * vec.x + this->data[1][1] * vec.y + this->data[1][2] * vec.z + this->data[1][3],
            this->data[2][0] * vec.x + this->data[2][1] * vec.y + this->data[2][2] * vec.z + this->data[2][3]
        };
    }

    template<typename T>
    constexpr mat4<T> mat4<T>::operator*(const mat4<T> &mat) const {
        mat4<T> retMat;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                retMat[i][j] = data[i][0] * mat[0][j] + data[i][1] * mat[1][j] + data[i][2] * mat[2][j] +
                               data[i][3] * mat[3][j];
            }
        }
        return retMat;
    }

    template<typename T>
    constexpr mat4<T> mat4<T>::multiply(const mat4<T> &mat) const {
        mat4<T> retMat;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                retMat[i][j] = data[i][0] * mat[0][j] + data[i][1] * mat[1][j] + data[i][2] * mat[2][j] +
                               data[i][3] * mat[3][j];
            }
        }
        return retMat;
    }

    template <typename T>
    vec2<T> mat4<T>::getPosition() const {
        T x = data[3][0];
        T y = data[3][1];
        return vec2<T>(x, y);
    }

    typedef mat4<float> mat4f;
    typedef mat4<double> mat4d;
    typedef mat4<int> mat4i;
    typedef mat4<std::uint32_t> mat4u;
}

