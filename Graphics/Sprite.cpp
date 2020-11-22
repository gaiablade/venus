#include "Sprite.hpp"

namespace vn {
    Sprite::Sprite(Tex2d& texture) :
            indices({0, 2, 3, 0, 3, 1}),
            buffer({ // position, texture-coordinates
                /*top-left*/     v(vec2f(-texture.getWidth()/2, (-texture.getHeight()/2)), vec2f(0.f, 0.f)),
                /*top-right*/    v(vec2f(texture.getWidth()/2, -texture.getHeight()/2), vec2f(1.f, 0.f)),
                /*bottom-left*/  v(vec2f(-texture.getWidth()/2, texture.getHeight()/2), vec2f(0.f, 1.f)),
                /*bottom-right*/ v(vec2f(texture.getWidth()/2, texture.getHeight()/2), vec2f(1.f, 1.f))
                   }),
            vbuffer(static_cast<const void *>(buffer.data()), buffer.size() * sizeof(v), GL_DYNAMIC_DRAW),
            ibuffer(static_cast<const void *>(indices.data()), indices.size() * sizeof(uint32_t)),
            dimensions({ static_cast<float>(texture.getWidth()), static_cast<float>(texture.getHeight()) })
    {
        this->attributes.Insert<float>(2);
        this->attributes.Insert<float>(2);
        this->varray.addBuffer(this->vbuffer, this->attributes);
        this->texture = &texture;
    }

    Sprite::Sprite(Sprite&& other) {
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

    mat4<float> Sprite::getModel() const {
        mat4<float> scaleMatrix = mat4<float>::scale2d(this->scale);
        mat4<float> rotationMatrix = mat4<float>::rotate2d(this->angle);
        mat4<float> translationMatrix = mat4<float>::translate2d(this->position);
        //return scaleMatrix * rotationMatrix * translationMatrix;
        return scaleMatrix * rotationMatrix * translationMatrix;
    }

    void Sprite::setPosition(const vec2<float> &p) {
        this->position = p;
    }

    void Sprite::setRotation(const float &a) {
        this->angle = a;
    }

    float Sprite::getRotation() const {
        return this->angle;
    }

    void Sprite::setScale(const vec2<float> &s) {
        this->scale = {flipped ? std::abs(s.x) * -1 : std::abs(s.x), s.y};
    }

    void Sprite::setSize(const vn::vec2f &size) {
        setScale(vn::vec2f(size.x / dimensions.x, size.y / dimensions.y));
    }

    void Sprite::setTexRectangle(float l, float t, float w, float h) {
        this->dimensions = vn::vec2f(w, h);
        auto size = vec2f{ (float)this->texture->getWidth(), (float)this->texture->getHeight() };
        float left = l * (1.f / size.x);
        float right = (l + w) * (1.f / size.x);
        float top = t * (1.f / size.y);
        float bottom = (t + h) * (1.f / size.y);
        /*
        float left = l;
        float right = l + w;
        float top = t;
        float bottom = t + h;
         */
        float width = w;
        float height = h;
        buffer[0].dimensions = vec2f(-width/2, -height/2);
        buffer[1].dimensions = vec2f(width/2, -height/2);
        buffer[2].dimensions = vec2f(-width/2, height/2);
        buffer[3].dimensions = vec2f(width/2, height/2);
        buffer[0].texCoords = vec2f(left, top);
        buffer[1].texCoords = vec2f(right, top);
        buffer[2].texCoords = vec2f(left, bottom);
        buffer[3].texCoords = vec2f(right, bottom);
        /*
        this->buffer[2] = left;
        this->buffer[3] = top;
        this->buffer[6] = right;
        this->buffer[7] = top;
        this->buffer[10] = left;
        this->buffer[11] = bottom;
        this->buffer[14] = right;
        this->buffer[15] = bottom;
         */
        this->varray.Bind();
        this->vbuffer.Bind();
        // TODO: Use glSubBufferData
        this->vbuffer.setData((const void*)(buffer.data()), sizeof(v) * buffer.size(), GL_DYNAMIC_DRAW);
    }

    vec2<float>& Sprite::getDimensions() {
        return this->dimensions;
    }

    vec2f Sprite::getScaledDimensions() const {
        return vec2f(dimensions.x * scale.x, dimensions.y * scale.y);
    }

    vec2f Sprite::getPosition() const {
        return this->position;
    }

    vec2f Sprite::getScale() const {
        return this->scale;
    }

    void Sprite::setFlipped(bool flipped) {
        this->flipped = flipped;
        this->setScale(scale);
    }
}
