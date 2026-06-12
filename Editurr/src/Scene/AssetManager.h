#pragma once

#include <vector>

#include "Material.h"
#include "Model.h"
#include "Render/Texture.hpp"

namespace Editurr
{
    typedef uint32_t AssetHandle;

    struct AssetManager
    {
        std::vector<MaterialData> m_materials{};
        std::vector<Rendurr::TextureData> m_textures{};
        std::vector<ModelData> m_models{};
    };

    AssetHandle material_create(AssetManager& assetManager);
    void material_add_texture(AssetManager& assetManager,
                              AssetHandle materialHandle,
                              AssetHandle textureHandle);
    void material_destroy();
    const MaterialData& asset_manager_get_material(const AssetManager& assetManager,
                                                   AssetHandle handle);

    AssetHandle texture_create(AssetManager& assetManager,
                               const std::filesystem::path& path,
                               Rendurr::TextureType type);
    const Rendurr::TextureData& asset_manager_get_texture(const AssetManager& assetManager,
                                                          AssetHandle handle);

    AssetHandle model_import_from_file(AssetManager& assetManager,
                                       const std::filesystem::path& path);
    const ModelData& asset_manager_get_model(const AssetManager& assetManager, AssetHandle handle);

} // namespace Editurr