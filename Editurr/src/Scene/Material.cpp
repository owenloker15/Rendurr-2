#include "Material.h"

#include "AssetManager.h"
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
} // namespace Editurr
