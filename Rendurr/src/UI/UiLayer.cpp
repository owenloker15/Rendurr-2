#include "UiLayer.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Core/Application.hpp"

namespace Rendurr
{
    void UiLayer::onAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Optional: allow multi-viewport

        // Setup style
        ImGui::StyleColorsDark();

        // When using viewports, tweak style
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGuiStyle& style = ImGui::GetStyle();
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Initialize backends
        auto test = Application::getInstance().getNativeWindow<GLFWwindow>();
        *test;
        ImGui_ImplGlfw_InitForOpenGL(Application::getInstance().getNativeWindow<GLFWwindow>(),
                                     true);     // your GLFW window
        ImGui_ImplOpenGL3_Init("#version 330"); // or your GLSL version
    }

    void UiLayer::onDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void UiLayer::startFrame()
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void UiLayer::endFrame()
    {
        ImGuiIO& io = ImGui::GetIO();
        auto window = Application::getInstance().getWindow();
        io.DisplaySize =
            ImVec2(static_cast<float>(window->getWidth()), static_cast<float>(window->getHeight()));

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
} // namespace Rendurr
