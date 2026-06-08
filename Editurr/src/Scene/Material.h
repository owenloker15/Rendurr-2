#pragma once

#include <filesystem>

#include "AssetManager.h"

namespace Editurr
{
    struct MaterialData
    {
        std::vector<AssetHandle> textureHandles;
    };

    AssetHandle material_create(AssetManager& assetManager);
    void material_add_texture(AssetManager& assetManager,
                              AssetHandle materialHandle,
                              AssetHandle textureHandle);
    void material_destroy();

} // namespace Editurr
