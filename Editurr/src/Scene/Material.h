#pragma once

#include <filesystem>

namespace Editurr
{
    typedef uint32_t AssetHandle;

    struct MaterialData
    {
        std::vector<AssetHandle> textureHandles;
    };

} // namespace Editurr
