#pragma once

#include "Material.h"
#include "Model.h"
#include "Render/Texture.hpp"
#include "Texture.h"

namespace Editurr
{
    struct AssetManager
    {
        std::vector<MaterialData> m_materials{};
        std::vector<Texture> m_textures{};
        std::vector<ModelData> m_models{};
    };

    // MATERIALS BEGIN
    AssetHandle material_create(AssetManager& assetManager);
    void material_add_texture(AssetManager& assetManager,
                              AssetHandle materialHandle,
                              AssetHandle textureHandle);
    void material_destroy();
    const MaterialData& asset_manager_get_material(const AssetManager& assetManager,
                                                   AssetHandle handle);
    // MATERIALS END

    // TEXTURES BEGIN
    AssetHandle texture_create(AssetManager& assetManager,
                               const std::filesystem::path& path,
                               Rendurr::TextureType type);
    const Texture& asset_manager_get_texture(const AssetManager& assetManager, AssetHandle handle);
    // TEXTURES END

    // MODELS BEGIN
    AssetHandle model_import_from_file(AssetManager& assetManager,
                                       const std::filesystem::path& path);
    const ModelData& asset_manager_get_model(const AssetManager& assetManager, AssetHandle handle);
    // MODELS END

} // namespace Editurr