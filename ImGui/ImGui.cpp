#include "ImGui.hpp"

namespace vn {
    ImGui::ImGui(Window &window) {
        ::ImGui::CreateContext();
        ImGuiIO& io = ::ImGui::GetIO(); (void)io;
        ::ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window.getGLFWWindow(), true);
        ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
    }

    ImGui::~ImGui() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ::ImGui::DestroyContext();
    }

    void ImGui::Render() {
        ::ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(::ImGui::GetDrawData());
    }

    void ImGui::NewFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ::ImGui::NewFrame();
    }

    void ImGui::Begin(const std::string& str) {
        ::ImGui::Begin(str.c_str());
    }

    void ImGui::End() {
        ::ImGui::End();
    }
}