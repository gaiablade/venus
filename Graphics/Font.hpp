#include "Tex2d.hpp"
#include "Sprite.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

namespace vn {
    struct Character {
        vec2f dimensions{};
        vec2f textureCoordinates{};
        vec2f bearing{};
        uint32_t advance{};
        Character(vec2f dimensions, vec2f texCoords, vec2f bearing, uint32_t advance) :
            dimensions(dimensions), textureCoordinates(texCoords), bearing(bearing), advance(advance) {}
        Character() =default;
    };

    class Font {
    public:
        Font(const std::string& filepath);
        ~Font() =default;
        Character& getCharacter(uint8_t c);
        vec2i& getDimensions();
        void Bind() const;
    private:
        Tex2d* texture;
        std::array<Character, 128> characters{};
        vec2i dimensions{};
    };
}
