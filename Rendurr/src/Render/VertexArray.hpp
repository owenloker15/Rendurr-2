#pragma once
#include <memory>

#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"

namespace rnd
{
    struct VertexArrayData
    {
        IndexBufferData ibData;
        VertexBufferData vbData;
        uint32_t rendererId;
    };

    VertexArrayData vertex_array_create(std::vector<Vertex>&& vertices,
                                        std::vector<uint32_t>&& indices);
    void vertex_array_destroy(uint32_t rendererId);

    void vertex_array_bind(uint32_t rendererId);
    void vertex_array_unbind();

} // namespace rnd
