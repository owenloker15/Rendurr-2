#pragma once

#include <vector>

#include "AssetHandle.h"

namespace Editurr
{
    struct MaterialData
    {
        std::vector<AssetHandle> textureHandles;
        AssetHandle handle = generate_asset_handle();
    };

} // namespace Editurr
