#include "VertexBuffer.hpp"

#include <Scene/Mesh.hpp>
#include <glad/glad.h>

namespace Rendurr
{

    VertexBuffer::VertexBuffer(std::vector<Vertex>&& vertices)
    {
        glCreateBuffers(1, &m_rendererId);
        glNamedBufferData(m_rendererId,
                          sizeof(Vertex) * vertices.size(),
                          vertices.data(),
                          GL_STATIC_DRAW);
    }

    void VertexBuffer::release()
    {
        glDeleteBuffers(1, &m_rendererId);
        m_rendererId = 0;
    }

    uint32_t VertexBuffer::getRendererId() const
    {
        return m_rendererId;
    }
} // namespace Rendurr
