#pragma once
#include "../Graphics/vec2.hpp"
#include "../Graphics/mat2.hpp"
#include <array>
#include <numbers>
#include <cmath>

namespace num = std::numbers;

namespace ga {
    class Collider {
    public:
        Collider() =delete;
        Collider(const vec2f& dimensions);
        bool isColliding(const Collider& other);
        void calculatePoints();

        void setPosition(const ga::vec2f& pos);
        void setRotation(const float& rotation);
        void setScale(const ga::vec2f& scale);

        vec2f dimensions;
        vec2f scaled_dimensions;
        vec2f bounding_dimensions;
        float rotation;
        vec2f position;
        std::array<vec2f, 4> points;
        std::array<vec2f, 4> rotated_points;
    };
}
