#include "Text.hpp"

namespace vn {
    Text::Text(const std::string& str, Font* font) : font(font) {
        auto length = str.length();
        characters.reserve(length);
        auto& dimensions = font->getDimensions();
        float offsetX{};
        int i{};
        for (auto& c: str) {
            auto& character = font->getCharacter(c);
            characters.emplace_back();
            characters.back().tl.position = vec2f(offsetX+character.bearing.x, -character.bearing.y);
            characters.back().tr.position = vec2f(offsetX+character.dimensions.x+character.bearing.x, -character.bearing.y);
            characters.back().bl.position = vec2f(offsetX+character.bearing.x, character.dimensions.y-character.bearing.y);
            characters.back().br.position = vec2f(offsetX+character.dimensions.x+character.bearing.x, character.dimensions.y-character.bearing.y);
            characters.back().tl.texCoords = vec2f(character.textureCoordinates.x/dimensions.x,
                                                   character.textureCoordinates.y/dimensions.y);
            characters.back().tr.texCoords = vec2f((character.textureCoordinates.x+character.dimensions.x)/dimensions.x,
                                                   character.textureCoordinates.y/dimensions.y);
            characters.back().bl.texCoords = vec2f(character.textureCoordinates.x/dimensions.x,
                                                   (character.textureCoordinates.y+character.dimensions.y)/dimensions.y);
            characters.back().br.texCoords = vec2f((character.textureCoordinates.x+character.dimensions.x)/dimensions.x,
                                                   (character.textureCoordinates.y+character.dimensions.y)/dimensions.y);
            indices.emplace_back(i);
            indices.emplace_back(i+2);
            indices.emplace_back(i+3);
            indices.emplace_back(i);
            indices.emplace_back(i+3);
            indices.emplace_back(i+1);
            i += 4;
            //offsetX += character.dimensions.x + 2;
            offsetX += character.advance >> 6;
        }
        vbuffer = new VBuffer((const void*)characters.data(), characters.size() * sizeof(Char));
        varray = new VArray();
        ibuffer = new IBuffer((const void*)indices.data(), sizeof(uint32_t) * indices.size());
        vattributes = new VAttributes();
        vattributes->Insert<float>(2);
        vattributes->Insert<float>(2);
        varray->addBuffer(*vbuffer, *vattributes);
    }

    Text::~Text() {
        delete this->vbuffer;
        delete this->varray;
        delete this->ibuffer;
    }

    void Text::Bind() const {
        this->font->Bind();
        this->varray->Bind();
        this->ibuffer->Bind();
    }

    mat4f Text::getModelView() const {
        return mat4f::translate2d(this->position);
    }

    std::vector<uint32_t> Text::getIndices() const {
        return this->indices;
    }
}
