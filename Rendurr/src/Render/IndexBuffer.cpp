#include "IndexBuffer.hpp"

#include <glad/glad.h>

namespace Rendurr
{
    IndexBuffer::IndexBuffer(std::vector<uint32_t>&& indices)
    {
        m_indexCount = indices.size();
        glCreateBuffers(1, &m_rendererId);
        glNamedBufferData(m_rendererId,
                          sizeof(uint32_t) * indices.size(),
                          indices.data(),
                          GL_STATIC_DRAW);
    }

    void IndexBuffer::release()
    {
        glDeleteBuffers(1, &m_rendererId);
        m_rendererId = 0;
    }

    uint32_t IndexBuffer::getRendererId() const
    {
        return m_rendererId;
    }

    uint32_t IndexBuffer::getIndexCount() const
    {
        return m_indexCount;
    }
} // namespace Rendurr
