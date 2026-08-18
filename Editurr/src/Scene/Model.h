#pragma once

#include <string>

#include "Mesh.h"

namespace Editurr
{
    struct ModelData
    {
        std::vector<MeshData> meshes{};
        std::string modelFile;
        AssetHandle handle = generate_asset_handle();
    };

} // namespace Editurr