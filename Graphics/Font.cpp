#include "Font.hpp"

namespace vn {
    Font::Font(const std::string &filepath) {
        FT_Library ft;
        if (FT_Init_FreeType(&ft)) {
            std::cerr << "Could not initialize FreeType Library" << std::endl;
            exit(1);
        }

        FT_Face face;
        if (FT_New_Face(ft, filepath.c_str(), 0, &face)) {
            std::cerr << "Could not load font" << std::endl;
            exit(1);
        }
        FT_Set_Pixel_Sizes(face, 0, 24);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // Calculate dimensions of texture:
        const int maxWidth = 800;
        int i_RowWidth = 0, i_RowHeight = 0;
        int i_TextureWidth = 0, i_TextureHeight = 0;
        for (unsigned char c = 0; c < 128; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cerr << "Failed to load glyph" << std::endl;
                exit(1);
            }
            if (i_RowWidth + face->glyph->bitmap.width + 1 >= maxWidth) {
                i_TextureWidth = i_TextureWidth > i_RowWidth ? i_TextureWidth : i_RowWidth;
                i_TextureHeight += i_RowHeight;
                i_RowWidth = 0;
                i_RowHeight = 0;
            }
            i_RowWidth += face->glyph->bitmap.width + 1;
            i_RowHeight = i_RowHeight > face->glyph->bitmap.rows ? i_RowHeight : face->glyph->bitmap.rows;
        }
        i_TextureWidth = i_TextureWidth > i_RowWidth ? i_TextureWidth : i_RowWidth;
        i_TextureHeight += i_RowHeight;

        dimensions = vec2i(i_TextureWidth, i_TextureHeight);
        texture = new Tex2d(nullptr, dimensions.x, dimensions.y);

        int offsetX{0}, offsetY{0};
        i_RowHeight = 0;
        for (uint8_t c = 0; c < 128; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cerr << "Failed to load glyph" << std::endl;
                exit(1);
            }
            if (offsetX + face->glyph->bitmap.width + 1 >= maxWidth) {
                offsetY += i_RowHeight;
                i_RowHeight = 0;
                offsetX = 0;
            }
            glTexSubImage2D(GL_TEXTURE_2D, 0, offsetX, offsetY, face->glyph->bitmap.width, face->glyph->bitmap.rows,
                            GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
            characters[c] = Character(vec2f(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                                      vec2f(offsetX, offsetY),
                                      vec2f(face->glyph->bitmap_left, face->glyph->bitmap_top),
                                      face->glyph->advance.x);

            i_RowHeight = i_RowHeight > face->glyph->bitmap.rows ? i_RowHeight : face->glyph->bitmap.rows;
            offsetX += face->glyph->bitmap.width + 1;
        }

        n_PeakHeight = i_RowHeight;

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }

    Character& Font::getCharacter(uint8_t c) {
        return this->characters[c];
    }

    vec2i& Font::getDimensions() {
        return this->dimensions;
    }

    void Font::Bind() const {
        this->texture->Bind();
    }

    int Font::getPeakHeight() const {
        return this->n_PeakHeight;
    }
}