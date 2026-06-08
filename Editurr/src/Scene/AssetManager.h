#pragma once

#include <vector>

#include "Render/Texture.hpp"

namespace Editurr
{
    typedef uint32_t AssetHandle;

    struct MaterialData;
    struct MeshData;

    struct AssetManager
    {
        std::vector<MaterialData> m_materials{};
        std::vector<Rendurr::TextureData> m_textures{};
        std::vector<MeshData> m_meshs{};
    };

    const MaterialData& asset_manager_get_material(const AssetManager& assetManager,
                                                   AssetHandle handle);
    const Rendurr::TextureData& asset_manager_get_texture(const AssetManager& assetManager,
                                                          uint32_t handle);
    const MeshData& asset_manager_get_mesh(const AssetManager& assetManager, AssetHandle handle);

} // namespace Editurr