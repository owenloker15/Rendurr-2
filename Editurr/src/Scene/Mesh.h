#pragma once

#include <vector>

#include "AssetManager.h"
#include "Render/VertexBuffer.hpp"

namespace Editurr
{
    struct MeshData
    {
        uint32_t vaRendererId;
        uint32_t vbRendererId;
        uint32_t ibRendererId;

        uint32_t indexCount;

        AssetHandle materialHandle;
    };

    AssetHandle mesh_create(AssetManager& assetManager,
                            std::vector<Rendurr::Vertex>&& vertices,
                            std::vector<uint32_t>&& indices,
                            AssetHandle materialHandle);
    void mesh_destroy(AssetHandle handle);

} // namespace Editurr
