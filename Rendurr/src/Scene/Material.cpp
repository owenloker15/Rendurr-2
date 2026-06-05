#include "Material.hpp"

#include "AssetManager.h"
#include "Render/Texture.hpp"

namespace Rendurr
{
    MaterialHandle material_create(AssetManager& assetManager)
    {
        // TODO handle what happens if material is deleted

        MaterialHandle handle = assetManager.m_materials.size();
        assetManager.m_materials.emplace_back();
        return handle;
    }

    void material_add_texture(AssetManager& assetManager,
                              MaterialHandle materialHandle,
                              TextureHandle textureHandle)
    {
        assetManager.m_materials[materialHandle].textureHandles.push_back(textureHandle);
    }
} // namespace Rendurr
