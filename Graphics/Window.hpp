#pragma once
#include <iostream>
#include <map>
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Model.hpp"
#include "Camera.hpp"
#include "OrthographicCamera.hpp"
#include "Orthographic3dCamera.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "vec2.hpp"
#include "GLCall.hpp"
#include "vec4.hpp"

namespace ga {
    struct WinParams {
        uint32_t width{800}, height{600};
        std::string title, f_VertexShader, f_FragmentShader;
        Camera camera;
    };

    class Window {
    public:
        Window(const WinParams &params);
        ~Window();
        void Clear() const;
        void Display() const;
        void Poll() const;
        bool Open() const;

        void AddShader(const std::string& name, const std::string& f_VertexShader, const std::string& f_FragmentShader);
        void UseShader(const std::string& name);

        void setBillboarding(const bool&);
        void setWireframe(const bool&);
        void setClearColor(const vec4f& color);

        template <typename Drawable>
        void Draw(const Drawable& object);

        GLFWwindow*& getGLFWWindow();
        WinParams& getAttributes();
        vec2<uint32_t> center();
    //protected:
        WinParams attributes;
        Camera camera;
        Renderer renderer;
        std::unordered_map<std::string, Shader> shaders;
        std::string s_CurrentShader{"Default"};
        // gl
        GLFWwindow* w;
    };
}

