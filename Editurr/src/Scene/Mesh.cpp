#include "Mesh.h"

#include "AssetManager.h"
#include "Render/VertexArray.hpp"

namespace Editurr
{
    AssetHandle mesh_create(AssetManager& assetManager,
                            std::vector<Rendurr::Vertex>&& vertices,
                            std::vector<uint32_t>&& indices,
                            AssetHandle materialHandle)
    {
        // TODO handle what happens if material is deleted
        AssetHandle handle = assetManager.m_meshs.size();

        Rendurr::VertexArrayData vaData =
            Rendurr::vertex_array_create(std::move(vertices), std::move(indices));

        MeshData data{.vaRendererId = vaData.rendererId,
                      .vbRendererId = vaData.vbData.rendererId,
                      .ibRendererId = vaData.ibData.rendererId,
                      .indexCount = vaData.ibData.indexCount,
                      .materialHandle = materialHandle};

        assetManager.m_meshs.insert(assetManager.m_meshs.begin() + handle, data);

        return handle;
    }

} // namespace Editurr
