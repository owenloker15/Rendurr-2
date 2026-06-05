#pragma once

#include <vector>

#include "Material.hpp"
#include "Render/VertexBuffer.hpp"

namespace Rendurr
{
    typedef uint32_t MeshHandle;

    struct MeshData
    {
        uint32_t vaRendererId;
        uint32_t vbRendererId;
        uint32_t ibRendererId;

        uint32_t indexCount;

        MaterialHandle mHandle;
    };

    MeshHandle mesh_create(AssetManager& assetManager,
                           std::vector<Vertex>&& vertices,
                           std::vector<uint32_t>&& indices,
                           MaterialHandle mHandle);
    void mesh_destroy(MeshHandle handle);

} // namespace Rendurr
