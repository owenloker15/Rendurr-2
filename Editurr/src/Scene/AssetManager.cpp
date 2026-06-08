#include "AssetManager.h"

#include "Material.h"
#include "Mesh.h"

namespace Editurr
{
    const MaterialData& asset_manager_get_material(const AssetManager& assetManager,
                                                   AssetHandle handle)
    {
        return assetManager.m_materials[handle];
    }

    const Rendurr::TextureData& asset_manager_get_texture(const AssetManager& assetManager,
                                                          AssetHandle handle)
    {
        return assetManager.m_textures[handle];
    }

    const MeshData& asset_manager_get_mesh(const AssetManager& assetManager, AssetHandle handle)
    {
        return assetManager.m_meshs[handle];
    }

} // namespace Editurr