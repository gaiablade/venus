#include "Font.hpp"
#include "VBuffer.hpp"
#include "VArray.hpp"
#include "VAttributes.hpp"
#include "IBuffer.hpp"
#include <fmt/core.h>
#include <ft2build.h>
#include FT_FREETYPE_H

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
        mat4f getModelView() const;
        std::vector<uint32_t> getIndices() const;
        vec2f position{};
        vec2f getDimensions() const;

        void setText(const std::string& str);
        void setTextFormatted(const std::string& str);
    private:
        std::vector<Char> characters;
        std::vector<uint32_t> indices;
        Font* font{nullptr};
        float maxWidth{};
        vec2f dimensions;

        VBuffer vbuffer;
        IBuffer ibuffer;
        VArray varray;
        VAttributes vattributes;
    };
}

