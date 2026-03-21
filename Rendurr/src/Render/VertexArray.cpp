#include "VertexArray.hpp"

#include <glad/glad.h>

namespace Rendurr
{
	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_rendererId);
	}

	VertexArray::VertexArray(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
	{
		glCreateVertexArrays(1, &m_rendererId);
		addVertexBuffer(std::make_unique<VertexBuffer>(vertices));
		setIndexBuffer(std::make_unique<IndexBuffer>(indices));
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

	void VertexArray::addVertexBuffer(std::unique_ptr<VertexBuffer> buffer)
	{
		m_vertexBuffer = std::move(buffer);
		glVertexArrayVertexBuffer(m_rendererId, 0, m_vertexBuffer->getRendererId(), 0, sizeof(Vertex));

		glEnableVertexArrayAttrib(m_rendererId, 0); // Position
		glEnableVertexArrayAttrib(m_rendererId, 1); // Normals
		glEnableVertexArrayAttrib(m_rendererId, 2); // Texture Coordinates

		glVertexArrayAttribFormat(m_rendererId, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
		glVertexArrayAttribFormat(m_rendererId, 1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, normal));
		glVertexArrayAttribFormat(m_rendererId, 2, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, texCoords));

		glVertexArrayAttribBinding(m_rendererId, 0, 0);
		glVertexArrayAttribBinding(m_rendererId, 1, 0);
		glVertexArrayAttribBinding(m_rendererId, 2, 0);
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
