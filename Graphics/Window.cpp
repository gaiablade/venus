#include "Window.hpp"

namespace ga {
    Window::Window(const WinParams &params) : attributes(params), camera(params.camera) {
        if (!glfwInit()) {
            std::cout << "Failed to initialize glfw.\n";
            exit(1);
        }

        this->w = glfwCreateWindow(params.width, params.height, params.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(this->w);
        glfwSwapInterval(1);

        glewInit();

        GLCall(glClearColor(0.f, 0.2f, 1.f, 1.f));
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glDepthFunc(GL_LEQUAL));

        this->shaders.insert(std::make_pair<std::string, Shader>("Default", {}));
        this->shaders["Default"].CreateShader(params.f_VertexShader, params.f_FragmentShader);
        this->shaders["Default"].Use();
    }

    Window::~Window() {
        if (this->w != nullptr) {
            glfwDestroyWindow(this->w);
        }
    }

    void Window::Clear() const {
        glClear(GL_DEPTH_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::Display() const {
        glfwSwapBuffers(this->w);
    }

    void Window::Poll() const {
        glfwPollEvents();
    }

    bool Window::Open() const {
        return !glfwWindowShouldClose(this->w);
    }

    void Window::AddShader(const std::string &name, const std::string &f_VertexShader,
                           const std::string &f_FragmentShader) {
        this->shaders.insert(std::make_pair<std::string, Shader>(name.c_str(), {}));
        this->shaders[name].CreateShader(f_VertexShader, f_FragmentShader);
    }

    void Window::UseShader(const std::string &name) {
        const auto it = this->shaders.find(name);
        if (it != this->shaders.end()) {
            this->s_CurrentShader = name;
            it->second.Use();
        }
    }

    void Window::setBillboarding(const bool &conditional) {
        if (conditional) {
            glDisable(GL_DEPTH_TEST);
        }
        else {
            glEnable(GL_DEPTH_TEST);
        }
    }

    void Window::setWireframe(const bool &conditional) {
        if (conditional) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }

    void Window::setClearColor(const vec4<float> &color) {
        GLCall(glClearColor(color.r, color.g, color.b, color.a));
    }

    const bool Window::IsKeyPressed(const key& code) const {
        auto status = glfwGetKey(this->w, (int) code);
        return status == GLFW_PRESS || status == GLFW_REPEAT;
    }

    GLFWwindow*& Window::getGLFWWindow() {
        return this->w;
    }

    WinParams& Window::getAttributes() {
        return this->attributes;
    }

    vec2<uint32_t> Window::center() {
        return {
                this->attributes.width / 2, this->attributes.height / 2
        };
    }

}
