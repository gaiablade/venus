#pragma once
#include "Font.hpp"
#include "VBuffer.hpp"
#include "VArray.hpp"
#include "VAttributes.hpp"
#include "IBuffer.hpp"
#include <fmt/core.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "vec4.hpp"

struct Vertex {
    vn::vec2f position, texCoords;
};

struct Char {
    Vertex tl{}, tr{}, bl{}, br{};
};

namespace vn {
    class Text {
    public:
        Text(const std::string& str, Font* font, float maxWidth = -1.f);
        Text(Text&& other) noexcept ;
        ~Text() =default;
        void Bind() const;
        mat4f getModel() const;
        vec4f getColor() const;
        std::vector<uint32_t> getIndices() const;
        vec2f position{};
        vec2f getDimensions() const;

        void setPosition(const vec2f& position);
        void setText(const std::string& str);
        void setTextFormatted(const std::string& str);
        void setVisibleChars(int num);
        void setTextColor(const vn::vec4f& color);
        [[nodiscard]] vec2f getPosition() const;
        [[nodiscard]] int getOpenGLDrawMode() const { return ogl_DrawMode; }
        void setOpenGLDrawMode(int mode) { this->ogl_DrawMode = mode; }
    private:
        std::vector<Char> characters;
        std::vector<uint32_t> indices;
        Font* font{nullptr};
        const float maxWidth;
        vec2f dimensions;
        vn::vec4f color{1, 1, 1, 1};

        // Opengl stuff
        VBuffer vbuffer;
        IBuffer ibuffer;
        VArray varray;
        VAttributes vattributes;
        int ogl_DrawMode = GL_TRIANGLES;
    };
}

