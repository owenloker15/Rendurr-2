#pragma once

#include <vector>

#include "Material.hpp"
#include "Mesh.hpp"

namespace Rendurr
{
    struct MaterialData;
    struct TextureData;
    struct MeshData;

    struct AssetManager
    {
        std::vector<MaterialData> m_materials{};
        std::vector<TextureData> m_textures{};
        std::vector<MeshData> m_meshs{};
    };

    const MaterialData& asset_manager_get_material(const AssetManager& assetManager,
                                                   MaterialHandle handle);
    const TextureData& asset_manager_get_texture(const AssetManager& assetManager,
                                                 TextureHandle handle);
    const MeshData& asset_manager_get_mesh(const AssetManager& assetManager, MeshHandle handle);

} // namespace Rendurr