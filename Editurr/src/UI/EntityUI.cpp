#include "EntityUI.h"

#include <imgui.h>

#include "../Editurr.h"
#include "glm/gtc/type_ptr.inl"

namespace
{
    void components_draw(Editurr::EditurrState& state, Editurr::Entity& entity)
    {
        ImGui::Begin("Components");

        ImGui::Text("Model");
        ImGui::SameLine();
        const auto& modelData = Editurr::asset_manager_get_model(state.assetManager, entity.model);
        ImGui::Text(modelData.modelFile.c_str());

        ImGui::SliderFloat3("Position",
                            glm::value_ptr(entity.transform.translation),
                            -50.0f,
                            100.0f);
        ImGui::SliderFloat3("Rotation", glm::value_ptr(entity.transform.rotation), -50.0f, 100.0f);
        ImGui::SliderFloat3("Scale", glm::value_ptr(entity.transform.scale), -50.0f, 100.0f);
        ImGui::End();
    }
} // namespace

namespace Editurr
{
    void entity_tree_draw(EditurrState& state)
    {
        ImGui::Begin("Entity Tree");

        for (auto& entity : state.activeScene.entities) {
            if (ImGui::TreeNode(entity.name)) {
                components_draw(state, entity);
                ImGui::TreePop();
            }
        }

        ImGui::End();
    }
} // namespace Editurr
