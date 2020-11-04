#include "Text.hpp"

struct Word {
    int i1, i2;
    Word(int i1, int i2) : i1(i1), i2(i2) {}
};

namespace vn {
    Text::Text(const std::string& str, Font* font, float maxWidth) : font(font), maxWidth(maxWidth) {
        vattributes.Insert<float>(2);
        vattributes.Insert<float>(2);
        varray.addBuffer(vbuffer, vattributes);
        setTextFormatted(str);
    }

    Text::Text(Text &&other)  noexcept :
        characters(std::move(other.characters)), indices(std::move(other.indices)),
        varray(std::move(other.varray)), vbuffer(std::move(other.vbuffer)),
        ibuffer(std::move(other.ibuffer)), font(other.font),
        maxWidth(other.maxWidth), dimensions(other.dimensions)
    {
    }

    void Text::Bind() const {
        this->font->Bind();
        this->varray.Bind();
        this->ibuffer.Bind();
    }

    mat4f Text::getModelView() const {
        return mat4f::translate2d(this->position);
    }

    vec4f Text::getColor() const {
        return this->color;
    }

    std::vector<uint32_t> Text::getIndices() const {
        return this->indices;
    }

    vec2f Text::getDimensions() const {
        return this->dimensions;
    }

    void Text::setText(const std::string &str) {
        auto length = str.length();
        characters.clear();
        indices.clear();
        characters.reserve(length);
        auto& fontDimensions = font->getDimensions();
        float offsetX{}, offsetY{};
        int i{};
        for (auto& c: str) {
            auto& character = font->getCharacter(c);
            if (maxWidth > 0 && offsetX + character.dimensions.x > this->maxWidth) {
                offsetX = 0;
                offsetY += (float)this->font->getPeakHeight();
                this->dimensions.y += (float)this->font->getPeakHeight();
            } else {
                this->dimensions.x = std::max(this->dimensions.x, offsetX + character.dimensions.x);
            }
            characters.emplace_back();
            characters.back().tl.position = vec2f(offsetX+character.bearing.x,
                                                  offsetY-character.bearing.y);

            characters.back().tr.position = vec2f(offsetX+character.dimensions.x+character.bearing.x,
                                                  offsetY-character.bearing.y);

            characters.back().bl.position = vec2f(offsetX+character.bearing.x,
                                                  offsetY+character.dimensions.y-character.bearing.y);

            characters.back().br.position = vec2f(offsetX+character.dimensions.x+character.bearing.x,
                                                  offsetY+character.dimensions.y-character.bearing.y);

            characters.back().tl.texCoords = vec2f(character.textureCoordinates.x/fontDimensions.x,
                                                   character.textureCoordinates.y/fontDimensions.y);
            characters.back().tr.texCoords = vec2f((character.textureCoordinates.x+character.dimensions.x)/fontDimensions.x,
                                                   character.textureCoordinates.y/fontDimensions.y);
            characters.back().bl.texCoords = vec2f(character.textureCoordinates.x/fontDimensions.x,
                                                   (character.textureCoordinates.y+character.dimensions.y)/fontDimensions.y);
            characters.back().br.texCoords = vec2f((character.textureCoordinates.x+character.dimensions.x)/fontDimensions.x,
                                                   (character.textureCoordinates.y+character.dimensions.y)/fontDimensions.y);
            indices.emplace_back(i);
            indices.emplace_back(i+2);
            indices.emplace_back(i+3);
            indices.emplace_back(i);
            indices.emplace_back(i+3);
            indices.emplace_back(i+1);
            i += 4;

            offsetX += character.advance >> 6;
        }
        vbuffer.setData((void*)characters.data(), characters.size() * sizeof(Char), GL_DYNAMIC_DRAW);
        ibuffer.setData((void*)indices.data(), indices.size() * sizeof(uint32_t), GL_DYNAMIC_DRAW);
    }

    void Text::setTextFormatted(const std::string &str) {
        auto length = str.length();
        characters.clear();
        indices.clear();
        indices.reserve(str.length() * 6);
        characters.reserve(length);
        this->dimensions = {};

        // Split string into separate words using space as a delimiter
        std::vector<std::string_view> words;
        int ind1 = -1;
        for (int i = 0; i < length; i++) {
            if (str[i] == ' ' || i == 0 || i == length - 1) {
                if (ind1 == -1) {
                    ind1 = i;
                } else {
                    words.emplace_back(std::string_view(&str.c_str()[ind1], i - ind1 + 1));
                    ind1 = i + 1;
                }
            }
        }

        auto& fontDimensions = font->getDimensions();
        float offsetX{}, offsetY{};
        int i{};
        for (auto& w: words) {
            int width{};
            for (auto& c: w) {
                auto ch = font->getCharacter(c);
                width += ch.advance >> 6;
            }
            if (offsetX + width > this->maxWidth) {
                offsetX = 0;
                offsetY += (float)this->font->getPeakHeight();
                this->dimensions.y += (float)this->font->getPeakHeight();
            }
            for (auto& c: w) {
                auto character = font->getCharacter(c);
                if (maxWidth > 0 && offsetX + character.dimensions.x > this->maxWidth) {
                    offsetX = 0;
                    offsetY += (float)this->font->getPeakHeight();
                    this->dimensions.y += (float)this->font->getPeakHeight();
                } else {
                    this->dimensions.x = std::max(this->dimensions.x, offsetX + (character.advance >> 6));
                }
                characters.emplace_back();
                characters.back().tl.position = vec2f(offsetX+character.bearing.x,
                                                      offsetY-character.bearing.y);

                characters.back().tr.position = vec2f(offsetX+character.dimensions.x+character.bearing.x,
                                                      offsetY-character.bearing.y);

                characters.back().bl.position = vec2f(offsetX+character.bearing.x,
                                                      offsetY+character.dimensions.y-character.bearing.y);

                characters.back().br.position = vec2f(offsetX+character.dimensions.x+character.bearing.x,
                                                      offsetY+character.dimensions.y-character.bearing.y);

                characters.back().tl.texCoords = vec2f(character.textureCoordinates.x/fontDimensions.x,
                                                       character.textureCoordinates.y/fontDimensions.y);
                characters.back().tr.texCoords = vec2f((character.textureCoordinates.x+character.dimensions.x)/fontDimensions.x,
                                                       character.textureCoordinates.y/fontDimensions.y);
                characters.back().bl.texCoords = vec2f(character.textureCoordinates.x/fontDimensions.x,
                                                       (character.textureCoordinates.y+character.dimensions.y)/fontDimensions.y);
                characters.back().br.texCoords = vec2f((character.textureCoordinates.x+character.dimensions.x)/fontDimensions.x,
                                                       (character.textureCoordinates.y+character.dimensions.y)/fontDimensions.y);
                indices.emplace_back(i);
                indices.emplace_back(i+2);
                indices.emplace_back(i+3);
                indices.emplace_back(i);
                indices.emplace_back(i+3);
                indices.emplace_back(i+1);
                i += 4;

                offsetX += character.advance >> 6;
            }
            auto space = font->getCharacter(' ');
            this->dimensions.x = std::max(this->dimensions.x, offsetX + space.dimensions.x);
            characters.emplace_back();
            characters.back().tl.position = vec2f(offsetX+space.bearing.x,
                                                  offsetY-space.bearing.y);

            characters.back().tr.position = vec2f(offsetX+space.dimensions.x+space.bearing.x,
                                                  offsetY-space.bearing.y);

            characters.back().bl.position = vec2f(offsetX+space.bearing.x,
                                                  offsetY+space.dimensions.y-space.bearing.y);

            characters.back().br.position = vec2f(offsetX+space.dimensions.x+space.bearing.x,
                                                  offsetY+space.dimensions.y-space.bearing.y);

            characters.back().tl.texCoords = vec2f(space.textureCoordinates.x/fontDimensions.x,
                                                   space.textureCoordinates.y/fontDimensions.y);
            characters.back().tr.texCoords = vec2f((space.textureCoordinates.x+space.dimensions.x)/fontDimensions.x,
                                                   space.textureCoordinates.y/fontDimensions.y);
            characters.back().bl.texCoords = vec2f(space.textureCoordinates.x/fontDimensions.x,
                                                   (space.textureCoordinates.y+space.dimensions.y)/fontDimensions.y);
            characters.back().br.texCoords = vec2f((space.textureCoordinates.x+space.dimensions.x)/fontDimensions.x,
                                                   (space.textureCoordinates.y+space.dimensions.y)/fontDimensions.y);
            indices.emplace_back(i);
            indices.emplace_back(i+2);
            indices.emplace_back(i+3);
            indices.emplace_back(i);
            indices.emplace_back(i+3);
            indices.emplace_back(i+1);
            i += 4;

            offsetX += space.advance >> 6;
        }
        vbuffer.setData((void*)characters.data(), characters.size() * sizeof(Char), GL_DYNAMIC_DRAW);
        ibuffer.setData((void*)indices.data(), indices.size() * sizeof(uint32_t), GL_DYNAMIC_DRAW);
    }

    void Text::setVisibleChars(int num) {
        this->indices.resize(6 * num);
    }

    void Text::setTextColor(const vn::vec4f& color) {
        this->color = color;
    }
}
