#include "Window.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

namespace vn {
    Window::Window(const WinParams &params) : attributes(params), camera(params.camera) {
        const fs::path p = fs::path(__FILE__).parent_path();

        if (!glfwInit()) {
            std::cout << "Failed to initialize glfw.\n";
            exit(1);
        }

        this->w = glfwCreateWindow(params.width, params.height, params.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(this->w);
        glfwSwapInterval(1);

        glewInit();

        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glDepthFunc(GL_LEQUAL));
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glClearColor(0.5f, 0.5f, 0.5f, 1.f));

        if (params.directory.empty()) {
            this->d_ShaderDirectory = p.parent_path();
        } else {
            this->d_ShaderDirectory = params.directory;
        }
        const fs::path v = d_ShaderDirectory / fs::path(params.f_VertexShader);
        const fs::path f = d_ShaderDirectory / fs::path(params.f_FragmentShader);

        this->shaders.insert(std::make_pair<std::string, Shader>("Default", {}));
        this->shaders["Default"].CreateShader(v.c_str(), f.c_str());
        this->shaders["Default"].Use();

        glfwSetFramebufferSizeCallback(w, framebuffer_size_callback);
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
        fs::path v_shader = this->d_ShaderDirectory / fs::path(f_VertexShader);
        fs::path f_shader = this->d_ShaderDirectory / fs::path(f_FragmentShader);
        this->shaders[name].CreateShader(v_shader.c_str(), f_shader.c_str());
    }

    void Window::UseShader(const std::string &name) {
        const auto it = this->shaders.find(name);
        if (it != this->shaders.end()) {
            this->s_CurrentShader = name;
            it->second.Use();
        }
    }

    Shader& Window::GetShader(const std::string &shaderName) {
        const auto it = this->shaders.find(shaderName);
        if (it != this->shaders.end()) {
            return it->second;
        }
        return this->shaders.at(s_CurrentShader);
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

    const bool Window::IsMouseButtonPressed(const key &code) const {
        auto status = glfwGetMouseButton(this->w, (int)code);
        return status == GLFW_PRESS || status == GLFW_REPEAT;
    }

    const vec2f Window::GetMousePosition() {
        double x, y;
        glfwGetCursorPos(getGLFWWindow(), &x, &y);
        return {(float)x, (float)y};
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

    vec2u Window::getDimensions() {
        int width, height;
        glfwGetWindowSize(this->w, &width, &height);
        return vec2u((uint32_t)width, (uint32_t)height);
    }

}
