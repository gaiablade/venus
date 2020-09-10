#include "Collider.hpp"

namespace ga {
    Collider::Collider(const vec2f& dimensions)
            : dimensions(dimensions), scaled_dimensions(dimensions), position({ 0.0f, 0.0f }), rotation(0.f)
    {
        this->points[0] = ga::vec2f{ this->position.x - dimensions.x / 2, this->position.y - dimensions.y / 2 }; // top left
        this->points[1] = ga::vec2f{ this->position.x + dimensions.x / 2, this->position.y - dimensions.y / 2 }; // top right
        this->points[2] = ga::vec2f{ this->position.x + dimensions.x / 2, this->position.y + dimensions.y / 2 }; // bottom right
        this->points[3] = ga::vec2f{ this->position.x - dimensions.x / 2, this->position.y + dimensions.y / 2 }; // bottom left
        calculatePoints();
        this->setRotation(this->rotation);
    }

    void Collider::setPosition(const vec2f& pos) {
        this->position = pos;
        calculatePoints();
    }

    void Collider::setRotation(const float& rotation) {
        this->rotation = rotation;

        // Calculate bounding box:
        /*
        this->bounding_dimensions.x  = abs(this->scaledWidth * cos(rotation.angle * PI / 180)) + abs(this->scaledHeight * sin(rotation.angle * PI / 180));
        this->bounding_dimensions.y = abs(this->scaledWidth * sin(rotation.angle * PI / 180)) + abs(this->scaledHeight * cos(rotation.angle * PI / 180));
         */
        this->bounding_dimensions.x = std::abs(this->scaled_dimensions.x * std::cos(rotation * num::pi / 180.f)) + std::abs(scaled_dimensions.y * std::sin(rotation * num::pi / 180.f));
        this->bounding_dimensions.y = std::abs(this->scaled_dimensions.x * std::sin(rotation * num::pi / 180.f)) + std::abs(scaled_dimensions.y * std::cos(rotation * num::pi / 180.f));

        calculatePoints();
    }

    void Collider::setScale(const vec2f& scale) {
        /*
        this->scaledWidth  = this->width  * scale.x;
        this->scaledHeight = this->height * scale.y;
         */
        this->scaled_dimensions.x = this->dimensions.x * scale.x;
        this->scaled_dimensions.y = this->dimensions.y * scale.y;
    }

    bool Collider::isColliding(const Collider& other) {
        // First use easy collision check with bounding boxes:
        if (this->position.x + bounding_dimensions.x / 2 < other.position.x - other.bounding_dimensions.x / 2 || other.position.x + other.bounding_dimensions.x / 2 < this->position.x - bounding_dimensions.x / 2) {
            return false;
        }
        if (this->position.y + bounding_dimensions.y / 2 < other.position.y - other.bounding_dimensions.y / 2 || other.position.y + other.bounding_dimensions.y / 2 < this->position.y - bounding_dimensions.y / 2) {
            return false;
        }

        // SAT-Theorem
        // Step 1: Get all normal angles
        /*
        ga::Angle normal_angles[4] = {
                ga::Angle(other.rotation.angle), ga::Angle(90.0f + other.rotation.angle),
                ga::Angle(this->rotation.angle), ga::Angle(90.0f + this->rotation.angle)
        };
         */
        std::array<float, 4> normal_angles = {
                other.rotation, 90 + other.rotation,
                this->rotation, 90 + this->rotation
        };

        // Step 2: Project the vectors onto the angles and determine min and max points
        for (int i = 0; i < 4; i++) {
            ga::mat2f mat = ga::mat2f::rotation(normal_angles[i]);
            ga::vec2f r_points[4] = {
                    /*
                    mat.multiply(points[0]), mat.multiply(points[1]),
                    mat.multiply(points[2]), mat.multiply(points[3])
                     */
                    mat * points[0], mat * points[1],
                    mat * points[2], mat * points[3]
            };
            ga::vec2f o_points[4] = {
                    /*
                    mat.multiply(other.points[0]), mat.multiply(other.points[1]),
                    mat.multiply(other.points[2]), mat.multiply(other.points[3])
                     */
                    mat * other.points[0], mat * other.points[1],
                    mat * other.points[1], mat * other.points[2]
            };
            // get min and max
            float tmin = r_points[0].x; float tmax = tmin;
            for (int j = 0; j < 4; j++) {
                if (r_points[j].x < tmin)
                    tmin = r_points[j].x;
                if (r_points[j].x > tmax)
                    tmax = r_points[j].x;
            }
            float omin = o_points[0].x; float omax = omin;
            for (int j = 0; j < 4; j++) {
                if (o_points[j].x < omin)
                    omin = o_points[j].x;
                if (o_points[j].x > omax)
                    omax = o_points[j].x;
            }
            // Step 3: Determine if there are gaps:
            if (tmax < omin || omax < tmin) {
                return false;
            }
        }
        return true;
    }

    void Collider::calculatePoints() {
        //ga::mat2f rotationMatrix(-this->rotation);
        ga::mat2f rotationMatrix = ga::mat2f::rotation(-this->rotation);
        ga::vec2f corners[4];
        // Rotate around center of box:
        /*
        corners[0] = rotationMatrix.multiply(ga::vec2f(0.0f - this->scaledWidth / 2, 0.0f - this->scaledHeight / 2));
        corners[1] = rotationMatrix.multiply(ga::vec2f(0.0f + this->scaledWidth / 2, 0.0f - this->scaledHeight / 2));
        corners[2] = rotationMatrix.multiply(ga::vec2f(0.0f + this->scaledWidth / 2, 0.0f + this->scaledHeight / 2));
        corners[3] = rotationMatrix.multiply(ga::vec2f(0.0f - this->scaledWidth / 2, 0.0f + this->scaledHeight / 2));
         */
        corners[0] = rotationMatrix * ga::vec2f{ 0.f - scaled_dimensions.x / 2, 0.f - scaled_dimensions.y / 2 };
        corners[1] = rotationMatrix * ga::vec2f{ 0.f + scaled_dimensions.x / 2, 0.f - scaled_dimensions.y / 2 };
        corners[2] = rotationMatrix * ga::vec2f{ 0.f+  scaled_dimensions.x / 2, 0.f + scaled_dimensions.y / 2 };
        corners[3] = rotationMatrix * ga::vec2f{ 0.f - scaled_dimensions.x / 2, 0.f + scaled_dimensions.y / 2 };
        // Set position according to position of box:
        for (int i = 0; i < 4; i++) {
            corners[i].x += this->position.x; corners[i].y += this->position.y;
            this->points[i] = corners[i];
        }
    }
}