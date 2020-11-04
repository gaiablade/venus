#pragma once
#include <iostream>
#include <filesystem>
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
#include "Keycodes.hpp"
#include "Text.hpp"

namespace fs = std::filesystem;

namespace vn {
    struct WinParams {
        uint32_t width{800}, height{600};
        std::string title, f_VertexShader, f_FragmentShader;
        Camera camera;

        std::string directory{};

        WinParams(const vec2f& dimensions, const std::string_view& title,
                  const std::string_view& v, const std::string_view& f, const Camera& cam,
                  const std::string_view& d = "")
            : width(dimensions.x), height(dimensions.y),
            title(title), f_VertexShader(v), f_FragmentShader(f), camera(cam), directory(d) {}
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
        Shader& GetShader(const std::string& shaderName);

        void setBillboarding(const bool&);
        void setWireframe(const bool&);
        void setClearColor(const vec4f& color);

        const bool IsKeyPressed(const key& code) const;
        const bool IsMouseButtonPressed(const key& code) const;
        const vec2f GetMousePosition();

        template <typename Drawable>
        void Draw(const Drawable& object);

        GLFWwindow*& getGLFWWindow();
        WinParams& getAttributes();
        vec2<uint32_t> center();
        vec2u getDimensions();
    //protected:
        WinParams attributes;
        Camera camera;
        Renderer renderer;
        std::unordered_map<std::string, Shader> shaders;
        std::string s_CurrentShader{"Default"};
        fs::path d_ShaderDirectory;
        // gl
        GLFWwindow* w;
    };

    template <typename Drawable>
    void Window::Draw(const Drawable& object) {
        mat4<float> u_MVP = object.getModelView() * this->camera.getProjection();
        this->shaders[s_CurrentShader].UniformMat4("u_MVP", u_MVP);
        this->renderer.Draw(object);
    }

    template <> inline
    void Window::Draw<Model>(const Model& object) {
        mat4<float> u_MVP = object.getModelView() * this->camera.getProjection();
        mat4f u_Model = object.getModelView();
        this->shaders[s_CurrentShader].UniformMat4("u_MVP", u_MVP);
        this->shaders[s_CurrentShader].UniformMat4("u_Model", u_Model);
        for (auto& mesh : object.meshes) {
            this->renderer.Draw(mesh);
        }
    }

    template <> inline
    void Window::Draw<Text>(const Text& object) {
        mat4<float> u_MVP = object.getModelView() * this->camera.getProjection();
        this->shaders[s_CurrentShader].UniformMat4("u_MVP", u_MVP);
        this->shaders[s_CurrentShader].UniformVec4f("u_TextColor", object.getColor());
        this->renderer.Draw(object);
    }
}

