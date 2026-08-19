#include "Mesh.h"

#include "Render/VertexArray.hpp"

namespace Editurr
{

    MeshData mesh_create(std::vector<rnd::Vertex>&& vertices,
                         std::vector<uint32_t>&& indices,
                         AssetHandle materialHandle)
    {
        rnd::VertexArrayData vaData =
            rnd::vertex_array_create(std::move(vertices), std::move(indices));

        return MeshData{.vaRendererId = vaData.rendererId,
                        .vbRendererId = vaData.vbData.rendererId,
                        .ibRendererId = vaData.ibData.rendererId,
                        .indexCount = vaData.ibData.indexCount,
                        .materialHandle = materialHandle};
        ;
    }

} // namespace Editurr
