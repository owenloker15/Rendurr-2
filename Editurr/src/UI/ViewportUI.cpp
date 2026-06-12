#include "ViewportUI.h"

#include <imgui.h>

#include "../Editurr.h"

namespace Editurr
{
    void viewport_draw(EditurrState& state)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Viewport");

        state.uiContext.viewportFocused = ImGui::IsWindowFocused();

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

        uint32_t newWidth = (uint32_t)viewportPanelSize.x;
        uint32_t newHeight = (uint32_t)viewportPanelSize.y;

        state.uiContext.viewportWidth = (float)newWidth;
        state.uiContext.viewportHeight = (float)newHeight;

        if (newWidth != state.renderContext.framebuffer.width ||
            newHeight != state.renderContext.framebuffer.height) {
            Rendurr::framebuffer_resize(state.renderContext.framebuffer, newWidth, newHeight);
        }

        uint32_t colorAttachmentTexture =
            Rendurr::framebuffer_get_color_attachment(state.renderContext.framebuffer, "color");
        ImGui::Image(colorAttachmentTexture,
                     ImVec2{state.uiContext.viewportWidth, state.uiContext.viewportHeight},
                     ImVec2(0, 1),
                     ImVec2(1, 0));

        ImGui::End();
        ImGui::PopStyleVar();
    }
} // namespace Editurr
