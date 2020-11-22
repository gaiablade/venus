#include "Circle.hpp"
#include <cmath>

namespace vn {
    std::array<float, (numPoints + 1) * 5> createCircleBuffer(const float &radius) {
        std::array<float, (numPoints + 1) * 5> retArr{};
        float radians_gap = 360.f / numPoints * M_PI / 180.f;
        retArr[0] = 0.f;
        retArr[1] = 0.f;
        retArr[2] = 1.f;
        retArr[3] = 0.f;
        retArr[4] = 0.f;
        for (int i = 1; i < numPoints + 1; i++) {
            retArr[5 * i + 0] = radius * std::cos(radians_gap * static_cast<float>(i));
            retArr[5 * i + 1] = radius * std::sin(radians_gap * static_cast<float>(i));
            retArr[5 * i + 2] = 1.f;
            retArr[5 * i + 3] = 0.f;
            retArr[5 * i + 4] = 0.f;
        }
        return retArr;
    }

    std::array<uint32_t, numPoints + 2> createIndexBuffer() {
        std::array<uint32_t, numPoints + 2> retArr{};
        for (int i = 0; i < numPoints + 2; i++) {
            retArr[i] = i;
        }
        retArr[numPoints + 1] = 1;
        return retArr;
    }

    Circle::Circle(const float &radius) : indices(createIndexBuffer()), buffer(createCircleBuffer(radius)),
                                          vbuffer(static_cast<const void *>(buffer.data()),
                                                  buffer.size() * sizeof(float)),
                                          ibuffer(static_cast<const void *>(indices.data()),
                                                  indices.size() * sizeof(uint32_t)) {
        this->attributes.Insert<float>(2);
        this->attributes.Insert<float>(3);
        this->varray.addBuffer(this->vbuffer, this->attributes);
    }

    void Circle::Bind() const {
        this->varray.Bind();
        this->ibuffer.Bind();
    }

    IBuffer &Circle::getIBuffer() {
        return this->ibuffer;

    }

    std::array<uint32_t, numPoints + 2> Circle::getIndices() const {
        return this->indices;
    }

    mat4<float> Circle::getModel() const {
        mat4<float> scaleMatrix = mat4<float>::scale2d(this->scale);
        mat4<float> rotationMatrix = mat4<float>::rotate2d(this->angle);
        mat4<float> translationMatrix = mat4<float>::translate2d(this->position);
        return scaleMatrix * rotationMatrix * translationMatrix;
    }

    void Circle::setPosition(const vec2<float> &p) {
        this->position = p;
    }

    void Circle::setRotation(const float &a) {
        this->angle = a;
    }

    void Circle::setScale(const vec2<float> &s) {
        this->scale = s;
    }
}