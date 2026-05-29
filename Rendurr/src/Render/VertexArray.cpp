#include "VertexArray.hpp"

#include <glad/glad.h>

namespace Rendurr
{
    VertexArray::VertexArray(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices)
        : m_vertexBuffer(std::move(vertices)), m_indexBuffer(std::move(indices))
    {
        glCreateVertexArrays(1, &m_rendererId);

        // Vertex Buffer
        glVertexArrayVertexBuffer(
            m_rendererId, 0, m_vertexBuffer.getRendererId(), 0, sizeof(Vertex));

        glEnableVertexArrayAttrib(m_rendererId, 0); // Position
        glEnableVertexArrayAttrib(m_rendererId, 1); // Normals
        glEnableVertexArrayAttrib(m_rendererId, 2); // Texture Coordinates

        glVertexArrayAttribFormat(
            m_rendererId, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
        glVertexArrayAttribFormat(m_rendererId, 1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, normal));
        glVertexArrayAttribFormat(
            m_rendererId, 2, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, texCoords));

        glVertexArrayAttribBinding(m_rendererId, 0, 0);
        glVertexArrayAttribBinding(m_rendererId, 1, 0);
        glVertexArrayAttribBinding(m_rendererId, 2, 0);

        // Index
        glVertexArrayElementBuffer(m_rendererId, m_indexBuffer.getRendererId());
    }

    void VertexArray::bind() const
    {
        glBindVertexArray(m_rendererId);
    }

    void VertexArray::unbind() const
    {
        glBindVertexArray(0);
    }

    void VertexArray::release()
    {
        glDeleteVertexArrays(1, &m_rendererId);
        m_rendererId = 0;
    }

    const IndexBuffer& VertexArray::getIndexBuffer() const
    {
        return m_indexBuffer;
    }
} // namespace Rendurr
