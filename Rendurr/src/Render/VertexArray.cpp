#include "VertexArray.hpp"

#include <glad/glad.h>

namespace Rendurr
{
	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_rendererId);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_rendererId);
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_rendererId);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::addVertexBuffer(const VertexBuffer* buffer)
	{
		// bind();
		// buffer->bind();
		// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		// glEnableVertexAttribArray(0);
		glVertexArrayVertexBuffer(m_rendererId, 0, buffer->getRendererId(), 0, sizeof(Vertex));
		glEnableVertexArrayAttrib(m_rendererId, 0);

		glVertexArrayAttribFormat(m_rendererId, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
		glVertexArrayAttribBinding(m_rendererId, 0, 0);
	}

	void VertexArray::setIndexBuffer(std::unique_ptr<IndexBuffer> buffer)
	{
		m_indexBuffer = std::move(buffer);
		glVertexArrayElementBuffer(m_rendererId, m_indexBuffer->getRendererId());
	}

	const std::unique_ptr<IndexBuffer>& VertexArray::getIndexBuffer() const
	{
		return m_indexBuffer;
	}
}
