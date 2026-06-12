#include "AssetManager.h"

#include "Material.h"
#include "Mesh.h"
#include "Render/Texture.hpp"

namespace Editurr
{
    AssetHandle material_create(AssetManager& assetManager)
    {
        // TODO handle what happens if material is deleted

        AssetHandle handle = assetManager.m_materials.size();
        assetManager.m_materials.emplace_back();
        return handle;
    }

    void material_add_texture(AssetManager& assetManager,
                              AssetHandle materialHandle,
                              AssetHandle textureHandle)
    {
        assetManager.m_materials[materialHandle].textureHandles.push_back(textureHandle);
    }

    const MaterialData& asset_manager_get_material(const AssetManager& assetManager,
                                                   AssetHandle handle)
    {
        return assetManager.m_materials[handle];
    }

    AssetHandle texture_create(AssetManager& assetManager,
                               const std::filesystem::path& path,
                               Rendurr::TextureType type)
    {
        AssetHandle handle = assetManager.m_textures.size();
        assetManager.m_textures.emplace_back(Rendurr::texture_create(path, type));
        return handle;
    }

    const Rendurr::TextureData& asset_manager_get_texture(const AssetManager& assetManager,
                                                          AssetHandle handle)
    {
        return assetManager.m_textures[handle];
    }

    const ModelData& asset_manager_get_model(const AssetManager& assetManager, AssetHandle handle)
    {
        return assetManager.m_models[handle];
    }

} // namespace Editurr