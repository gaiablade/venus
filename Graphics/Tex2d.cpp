#include "Tex2d.hpp"

namespace vn {
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

        //GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        //GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->n_TexWidth, this->n_TexHeight, 0, GL_RGBA,
                            GL_UNSIGNED_BYTE, (const void*)image_data));

        delete[] image_data;
    }

    Tex2d::Tex2d(uint8_t* buffer, int width, int height) {
        GLCall(glGenTextures(1, &this->n_TexID));
        GLCall(glBindTexture(GL_TEXTURE_2D, this->n_TexID));

        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height,
                            0, GL_RED, GL_UNSIGNED_BYTE, buffer));

        this->n_TexWidth = width;
        this->n_TexHeight = height;
    }

    Tex2d::Tex2d(Tex2d &&other)  noexcept :
        n_TexID(other.n_TexID), n_TexWidth(other.n_TexWidth), n_TexHeight(other.n_TexHeight),
        n_BytesPerPixel(other.n_BytesPerPixel)
    {
        other.n_TexID = 0;
    }

    Tex2d::~Tex2d() {
        GLCall(glDeleteTextures(1, &this->n_TexID));
    }

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
