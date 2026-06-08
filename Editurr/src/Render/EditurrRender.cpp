#include "EditurrRender.h"

#include "../Scene/Material.h"
#include "glm/ext/matrix_transform.hpp"
#include "Render/Renderer.hpp"
#include "Render/Shader.hpp"

namespace Editurr
{
    void render_scene(const Scene& scene,
                      const AssetManager& assetManager,
                      const Rendurr::ShaderData& shader)
    {
        Rendurr::shader_program_use(shader);

        scene.forEachEntity([&scene, &assetManager, &shader](Entity entity) {
            const TransformComponent& transformComponent = scene.getTransformComponent(entity);
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::translate(transform, transformComponent.translation);
            transform = glm::rotate(transform,
                                    glm::radians(transformComponent.rotation.x),
                                    glm::vec3(1.0f, 0.0f, 0.0f));
            transform = glm::rotate(transform,
                                    glm::radians(transformComponent.rotation.y),
                                    glm::vec3(0.0f, 1.0f, 0.0f));
            transform = glm::rotate(transform,
                                    glm::radians(transformComponent.rotation.z),
                                    glm::vec3(0.0f, 0.0f, 1.0f));
            transform = glm::scale(transform, transformComponent.scale);

            Rendurr::shader_uniform_upload_mat4(shader, "u_Transform", transform);

            const MeshComponent& meshComponent = scene.getMeshComponent(entity);
            const auto& meshData = asset_manager_get_mesh(assetManager, meshComponent.handle);
            const auto& materialData =
                asset_manager_get_material(assetManager, meshData.materialHandle);
            for (const auto& textureId : materialData.textureHandles) {
                const auto& textureData = asset_manager_get_texture(assetManager, textureId);
                Rendurr::upload_texture_to_shader(textureData, shader);
            }
            Rendurr::drawIndexed(meshData.vaRendererId, meshData.indexCount);
        });
    }
} // namespace Editurr