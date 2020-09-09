#include "Sprite.hpp"

namespace ga {
    Sprite::Sprite(Tex2d& texture) :
            indices({0, 2, 3, 0, 3, 1}),
            buffer({
                /*top-left*/     static_cast<float>(-texture.getWidth()/2), static_cast<float>(-texture.getHeight()/2), 0.f, 0.f ,
                /*top-right*/    static_cast<float>( texture.getWidth()/2), static_cast<float>(-texture.getHeight()/2), 1.f, 0.f,
                /*bottom-left*/  static_cast<float>(-texture.getWidth()/2), static_cast<float>( texture.getHeight()/2), 0.f, 1.f,
                /*bottom-right*/ static_cast<float>( texture.getWidth()/2), static_cast<float>( texture.getHeight()/2), 1.f, 1.f
                   }),
            vbuffer(static_cast<const void *>(buffer.data()), buffer.size() * sizeof(float)),
            ibuffer(static_cast<const void *>(indices.data()), indices.size() * sizeof(uint32_t)),
            dimensions({ static_cast<float>(texture.getWidth()), static_cast<float>(texture.getHeight()) })
    {
        this->attributes.Insert<float>(2);
        this->attributes.Insert<float>(2);
        this->varray.addBuffer(this->vbuffer, this->attributes);
        this->texture = &texture;
    }

    void Sprite::Bind() const {
        this->varray.Bind();
        this->ibuffer.Bind();
        this->texture->Bind();
    }

    IBuffer &Sprite::getIBuffer() {
        return this->ibuffer;
    }

    std::array<uint32_t, 6> Sprite::getIndices() const {
        return this->indices;
    }

    mat4<float> Sprite::getModelView() const {
        mat4<float> scaleMatrix = mat4<float>::scale2d(this->scale);
        mat4<float> rotationMatrix = mat4<float>::rotate2d(this->angle);
        mat4<float> translationMatrix = mat4<float>::translate2d(this->position);
        return scaleMatrix * rotationMatrix * translationMatrix;
    }

    void Sprite::setPosition(const vec2<float> &p) {
        this->position = p;
    }

    void Sprite::setRotation(const float &a) {
        this->angle = a;
    }

    void Sprite::setScale(const vec2<float> &s) {
        this->scale = s;
    }

    vec2<float>& Sprite::getDimensions() {
        return this->dimensions;
    }

    vec2<float> Sprite::getPosition() const {
        return this->position;
    }
}
