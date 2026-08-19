#pragma once

#include <vector>

#include "AssetHandle.h"
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

    MeshData mesh_create(std::vector<rnd::Vertex>&& vertices,
                         std::vector<uint32_t>&& indices,
                         AssetHandle materialHandle);
    void mesh_destroy(AssetHandle handle);

} // namespace Editurr
