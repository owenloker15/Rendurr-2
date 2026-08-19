#include "EntityUI.h"

#include <imgui.h>

#include "../Editurr.h"
#include "glm/gtc/type_ptr.inl"

namespace
{
    void components_draw(Editurr::EditurrState& state, Editurr::Entity& entity)
    {
        ImGui::Begin("Components");

        std::string previewValue;
        if (Editurr::is_valid_handle(entity.model)) {
            previewValue =
                Editurr::asset_manager_get_model(state.assetManager, entity.model).modelFile;
        }

        // Model selector
        if (ImGui::BeginCombo("##Model", previewValue.c_str())) {
            for (const auto& modelData : state.assetManager.m_models) {
                const bool selected = (modelData.handle == entity.model);

                if (ImGui::Selectable(modelData.modelFile.c_str(), selected)) {
                    entity.model = modelData.handle;
                }

                if (selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndCombo();
        }

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

        ImGuiTreeNodeFlags flags =
            ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;

        for (auto& entity : state.activeScene.entities) {
            ImGui::PushID(entity.id);

            ImGuiTreeNodeFlags node_flags = flags;

            if (state.uiContext.selectedEntity == entity.id)
                node_flags |= ImGuiTreeNodeFlags_Selected;

            bool open = ImGui::TreeNodeEx(entity.name, node_flags);

            // Select on left click.
            if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
                state.uiContext.selectedEntity = entity.id;
            }

            // Select and open context menu on right click.
            if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
                state.uiContext.selectedEntity = entity.id;
                ImGui::OpenPopup("EntityContextMenu");
            }

            if (open) {
                // Draw children here.

                ImGui::TreePop();
            }

            ImGui::PopID();
        }

        // Context menu for an entity.
        if (ImGui::BeginPopup("EntityContextMenu")) {
            if (auto entity =
                    scene_find_entity_with_id(state.activeScene, state.uiContext.selectedEntity)) {
                if (ImGui::MenuItem("Delete")) {
                    scene_delete_entity(state.activeScene, state.uiContext.selectedEntity);
                    state.uiContext.selectedEntity = INVALID_ENTITY_ID;
                }

                if (ImGui::MenuItem("Rename")) {
                    // Rename entity.value()
                }
            }

            ImGui::EndPopup();
        }

        // Context menu for empty space.
        if (ImGui::BeginPopupContextWindow("EntityTreeContextMenu",
                                           ImGuiPopupFlags_MouseButtonRight)) {
            if (ImGui::MenuItem("Create Entity")) {
                scene_create_entity(state.activeScene, "entity");
            }

            if (ImGui::MenuItem("Delete Selected")) {
                if (state.uiContext.selectedEntity != INVALID_ENTITY_ID) {
                    scene_delete_entity(state.activeScene, state.uiContext.selectedEntity);

                    state.uiContext.selectedEntity = INVALID_ENTITY_ID;
                }
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Expand All")) {
                // TODO
            }

            if (ImGui::MenuItem("Collapse All")) {
                // TODO
            }

            ImGui::EndPopup();
        }

        // Draw inspector for selected entity.
        if (auto entity =
                scene_find_entity_with_id(state.activeScene, state.uiContext.selectedEntity)) {
            components_draw(state, *entity);
        }

        ImGui::End();
    }
} // namespace Editurr
