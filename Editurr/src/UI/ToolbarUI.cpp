#include "ToolbarUI.h"

#include <imgui.h>

#include "../Editurr.h"

namespace Editurr
{
    void toolbar_draw(EditurrState& state)
    {
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit")) {
                    // TODO close app
                    state.input.windowCloseRequested = true;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
    }
} // namespace Editurr
