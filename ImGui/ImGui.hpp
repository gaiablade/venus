#pragma once
#include "../Graphics.hpp"
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

namespace vn {
    class ImGui {
    public:
        ImGui(Window& window);
        ~ImGui();
        void Render();
        void NewFrame();
        void Begin(const std::string& str);
        void End();
    private:
    };
}
