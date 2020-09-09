#include "Tex2d.hpp"

namespace ga {
    Tex2d::Tex2d(const std::string &filename) {
        std::filesystem::path filepath(filename);
        if (!std::filesystem::exists(filepath)) {
            std::cout << "Could not open file " << filename << std::endl;
            exit(1);
        }
        uint8_t* image_data = stbi_load(filename.c_str(), &this->n_TexWidth, &this->n_TexHeight, &this->n_BytesPerPixel, 4);
        if (!image_data) {
            std::cerr << "Could not load image file: \"" << filename << "\"\n";
            exit(1);
        }

        GLCall(glGenTextures(1, &this->n_TexID));
        GLCall(glBindTexture(GL_TEXTURE_2D, this->n_TexID));

        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->n_TexWidth, this->n_TexHeight, 0, GL_RGBA,
                            GL_UNSIGNED_BYTE, (const void*)image_data));

        delete[] image_data;
    }

    /*
    Tex2d::Tex2d(Tex2d &&source) noexcept
        : n_TexID(source.n_TexID), n_TexWidth(source.n_TexWidth), n_TexHeight(source.n_TexHeight), n_BytesPerPixel(source.n_BytesPerPixel)
    {
        source.n_TexID = 0;
    }
     */

    void Tex2d::Bind(const int& slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, this->n_TexID);
    }

    int Tex2d::getWidth() const {
        return this->n_TexWidth;
    }

    int Tex2d::getHeight() const {
        return this->n_TexHeight;
    }
}
