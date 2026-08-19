#include "UI.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Editurr
{
    void ui_init(rnd::Window& window)
    {
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
        ImGui_ImplGlfw_InitForOpenGL(window.glfwWindow, true); // your GLFW window
        ImGui_ImplOpenGL3_Init("#version 330");                // or your GLSL version
    }

    void ui_shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ui_frame_begin()
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ui_frame_end()
    {
        ImGuiIO& io = ImGui::GetIO();

        // Finish ImGui frame → generate draw data
        ImGui::Render();

        // Render main viewport (your OpenGL scene is usually drawn before this)
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Multi-viewport support (optional but correct if enabled)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_context = glfwGetCurrentContext();

            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();

            glfwMakeContextCurrent(backup_context);
        }
    }
} // namespace Editurr