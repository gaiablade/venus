#pragma once
#include <iostream>
#include <array>
#include <filesystem>
#include <GL/glew.h>
#include "GLCall.hpp"
#include "../vendor/stb_image/stb_image.h"

namespace vn {
    template <size_t n_Width, size_t n_Height>
    struct tex_data {
        size_t width = n_Width, height = n_Height;
        std::array<std::uint8_t, n_Width * n_Height * 3> data;
    };

    class Tex2d {
    public:

        Tex2d() = default;

        // Templated Constructor for use with embedded textures
        template <size_t n_Width, size_t n_Height>
        explicit Tex2d(const tex_data<n_Width, n_Height>& data);

        // Generic constructor for use with image files
        Tex2d(const std::string& filename);

        // Text
        Tex2d(uint8_t* buffer, int width, int height);

        // Move constructor:
        //Tex2d(Tex2d&& other);

        void Bind(const int& slot = 0) const;

        int getWidth() const;
        int getHeight() const;
        int getWidth() { return this->n_TexWidth; }
        int getHeight() { return this->n_TexHeight; }
        int getTexID() { return this->n_TexID; }
    private:
        uint32_t n_TexID{};

        int n_TexWidth{};
        int n_TexHeight{};
        int n_BytesPerPixel{};
    };

    template <size_t n_Width, size_t n_Height>
    Tex2d::Tex2d(const tex_data<n_Width, n_Height>& data) : n_TexWidth(n_Width), n_TexHeight(n_Height)
    {
        GLCall(glGenTextures(1, &this->n_TexID));
        GLCall(glBindTexture(GL_TEXTURE_2D, this->n_TexID));

        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, n_Width, n_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, (const void*)data.data.data()));
    }
}

