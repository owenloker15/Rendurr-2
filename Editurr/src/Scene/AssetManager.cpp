#include "AssetManager.h"

#include <algorithm>
#include <cassert>

#include "Material.h"
#include "Mesh.h"
#include "Render/Texture.hpp"

namespace Editurr
{
    AssetHandle material_create(AssetManager& assetManager)
    {
        // TODO handle what happens if material is deleted

        MaterialData material;
        const auto handle = material.handle;
        assetManager.m_materials.emplace_back(std::move(material));
        return handle;
    }

    void material_add_texture(AssetManager& assetManager,
                              AssetHandle materialHandle,
                              AssetHandle textureHandle)
    {
        const auto it = std::find_if(assetManager.m_materials.begin(),
                                     assetManager.m_materials.end(),
                                     [materialHandle](const MaterialData& material) {
                                         return material.handle == materialHandle;
                                     });

        assert(it != assetManager.m_materials.end());
        it->textureHandles.push_back(textureHandle);
    }

    const MaterialData& asset_manager_get_material(const AssetManager& assetManager,
                                                   AssetHandle handle)
    {
        const auto it = std::find_if(assetManager.m_materials.begin(),
                                     assetManager.m_materials.end(),
                                     [handle](const MaterialData& material) {
                                         return material.handle == handle;
                                     });

        assert(it != assetManager.m_materials.end());
        return *it;
    }

    AssetHandle texture_create(AssetManager& assetManager,
                               const std::filesystem::path& path,
                               Rendurr::TextureType type)
    {
        Texture texture{.textureData = texture_create(path, type)};
        const auto handle = texture.handle;
        assetManager.m_textures.push_back(std::move(texture));
        return handle;
    }

    const Texture& asset_manager_get_texture(const AssetManager& assetManager, AssetHandle handle)
    {
        const auto it = std::find_if(assetManager.m_textures.begin(),
                                     assetManager.m_textures.end(),
                                     [handle](const Texture& texture) {
                                         return texture.handle == handle;
                                     });

        assert(it != assetManager.m_textures.end());
        return *it;
    }

    const ModelData& asset_manager_get_model(const AssetManager& assetManager, AssetHandle handle)
    {
        const auto it = std::find_if(assetManager.m_models.begin(),
                                     assetManager.m_models.end(),
                                     [handle](const ModelData& model) {
                                         return model.handle == handle;
                                     });

        assert(it != assetManager.m_models.end());
        return *it;
    }

} // namespace Editurr
