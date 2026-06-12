#include "Mesh.h"

#include "Render/VertexArray.hpp"

namespace Editurr
{

    MeshData mesh_create(std::vector<Rendurr::Vertex>&& vertices,
                         std::vector<uint32_t>&& indices,
                         AssetHandle materialHandle)
    {
        Rendurr::VertexArrayData vaData =
            Rendurr::vertex_array_create(std::move(vertices), std::move(indices));

        return MeshData{.vaRendererId = vaData.rendererId,
                        .vbRendererId = vaData.vbData.rendererId,
                        .ibRendererId = vaData.ibData.rendererId,
                        .indexCount = vaData.ibData.indexCount,
                        .materialHandle = materialHandle};
        ;
    }

} // namespace Editurr
