#include "IndexBuffer.hpp"

#include <glad/glad.h>

namespace Rendurr
{
	IndexBuffer::IndexBuffer(const std::vector<uint32_t>& indices)
	{
		m_indexCount = indices.size();
		glCreateBuffers(1, &m_rendererId);
		glNamedBufferData(m_rendererId, sizeof(uint32_t) * indices.size(), indices.data(), GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_rendererId);
	}

	void IndexBuffer::bind() const
	{
	}

	void IndexBuffer::unbind() const
	{
	}

	uint32_t IndexBuffer::getRendererId() const
	{
		return m_rendererId;
	}

	uint32_t IndexBuffer::getIndexCount() const
	{
		return m_indexCount;
	}
}
