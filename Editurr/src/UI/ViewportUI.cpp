#include "ViewportUI.h"

#include <imgui.h>

#include "../Editurr.h"

namespace Editurr
{
    void viewport_draw(EditurrState& state)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Viewport");

        /*
        m_viewportFocused = ImGui::IsWindowFocused();
        Application::Get().GetUILayer()->BlockEvents(!m_viewportFocused);
        */

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        state.uiContext.viewportWidth = viewportPanelSize.x;
        state.uiContext.viewportHeight = viewportPanelSize.y;

        uint32_t textureID = state.renderContext.framebuffer.getColorAttachmentId("color");
        ImGui::Image(textureID,
                     ImVec2{state.uiContext.viewportWidth, state.uiContext.viewportHeight},
                     ImVec2(0, 1),
                     ImVec2(1, 0));

        ImGui::End();
        ImGui::PopStyleVar();
    }
} // namespace Editurr
