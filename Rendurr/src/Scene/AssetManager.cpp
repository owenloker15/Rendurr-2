#include "AssetManager.h"

#include "Mesh.hpp"

namespace Rendurr
{
    const MaterialData& asset_manager_get_material(const AssetManager& assetManager,
                                                   MaterialHandle handle)
    {
        return assetManager.m_materials[handle];
    }

    const TextureData& asset_manager_get_texture(const AssetManager& assetManager,
                                                 TextureHandle handle)
    {
        return assetManager.m_textures[handle];
    }

    const MeshData& asset_manager_get_mesh(const AssetManager& assetManager, MeshHandle handle)
    {
        return assetManager.m_meshs[handle];
    }

} // namespace Rendurr