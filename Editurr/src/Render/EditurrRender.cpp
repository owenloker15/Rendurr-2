#include "EditurrRender.h"

#include "../Scene/Material.h"
#include "../Scene/Mesh.h"
#include "../Scene/Model.h"
#include "glm/ext/matrix_transform.hpp"
#include "Render/Renderer.hpp"
#include "Render/Shader.hpp"

namespace
{
    void render_mesh(const Editurr::AssetManager& assetManager,
                     const Rendurr::ShaderData& shader,
                     const Editurr::MeshData& meshData)
    {
        const auto& materialData =
            asset_manager_get_material(assetManager, meshData.materialHandle);
        for (const auto& textureId : materialData.textureHandles) {
            const auto& texture = asset_manager_get_texture(assetManager, textureId);
            Rendurr::upload_texture_to_shader(texture.textureData, shader);
        }
        Rendurr::drawIndexed(meshData.vaRendererId, meshData.indexCount);
    }
} // namespace

namespace Editurr
{
    void render_scene(const Scene& scene,
                      const AssetManager& assetManager,
                      const Rendurr::ShaderData& shader)
    {
        Rendurr::shader_program_use(shader);

        for (const auto& entity : scene.entities) {
            // Transform
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::translate(transform, entity.transform.translation);
            transform = glm::rotate(transform,
                                    glm::radians(entity.transform.rotation.x),
                                    glm::vec3(1.0f, 0.0f, 0.0f));
            transform = glm::rotate(transform,
                                    glm::radians(entity.transform.rotation.y),
                                    glm::vec3(0.0f, 1.0f, 0.0f));
            transform = glm::rotate(transform,
                                    glm::radians(entity.transform.rotation.z),
                                    glm::vec3(0.0f, 0.0f, 1.0f));
            transform = glm::scale(transform, entity.transform.scale);
            Rendurr::shader_uniform_upload_mat4(shader, "u_Transform", transform);
            // End transform

            // Begin Model
            if (is_valid_handle(entity.model)) {
                const auto& modelData = asset_manager_get_model(assetManager, entity.model);
                for (const auto& meshData : modelData.meshes) {
                    render_mesh(assetManager, shader, meshData);
                }
            }
            // End Model
        }
    }
} // namespace Editurr