#include "VertexBuffer.hpp"

#include <glad/glad.h>

namespace Rendurr
{
    VertexBufferData vertex_buffer_create(std::vector<Vertex>&& vertices)
    {
        VertexBufferData data;

        glCreateBuffers(1, &data.rendererId);
        glNamedBufferData(data.rendererId,
                          sizeof(Vertex) * vertices.size(),
                          vertices.data(),
                          GL_STATIC_DRAW);

        return data;
    }

    void vertex_buffer_destroy(uint32_t rendererId)
    {
        glDeleteBuffers(1, &rendererId);
    }

} // namespace Rendurr
