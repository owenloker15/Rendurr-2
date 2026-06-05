#pragma once

#include <filesystem>

#include "Render/Texture.hpp"

namespace Rendurr
{
    typedef uint32_t MaterialHandle;

    struct MaterialData
    {
        std::vector<TextureHandle> textureHandles;
    };

    MaterialHandle material_create(AssetManager& assetManager);
    void material_add_texture(AssetManager& assetManager,
                              MaterialHandle materialHandle,
                              TextureHandle textureHandle);
    void material_destroy();

} // namespace Rendurr
