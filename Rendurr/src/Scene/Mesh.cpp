#include "Mesh.hpp"

#include "AssetManager.h"
#include "Render/VertexArray.hpp"

namespace Rendurr
{
    MeshHandle mesh_create(AssetManager& assetManager,
                           std::vector<Vertex>&& vertices,
                           std::vector<uint32_t>&& indices,
                           MaterialHandle mHandle)
    {
        // TODO handle what happens if material is deleted
        MeshHandle handle = assetManager.m_meshs.size();

        VertexArrayData vaData = vertex_array_create(std::move(vertices), std::move(indices));

        MeshData data{.vaRendererId = vaData.rendererId,
                      .vbRendererId = vaData.vbData.rendererId,
                      .ibRendererId = vaData.ibData.rendererId,
                      .indexCount = vaData.ibData.indexCount,
                      .mHandle = mHandle};

        assetManager.m_meshs.insert(assetManager.m_meshs.begin() + handle, data);

        return handle;
    }

} // namespace Rendurr
