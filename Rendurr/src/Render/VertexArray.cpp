#include "VertexArray.hpp"
#include "IndexBuffer.hpp"

#include <glad/glad.h>

namespace Rendurr
{
	VertexArray::VertexArray(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
	{
		glCreateVertexArrays(1, &m_rendererId);

		setVertexBuffer(create_vertex_buffer(vertices));
		setIndexBuffer(create_index_buffer(indices));

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

	void VertexArray::setVertexBuffer(uint32_t id)
	{
		m_vertexBufferId = id;
		glVertexArrayVertexBuffer(m_rendererId, 0, m_vertexBufferId, 0, sizeof(Vertex));

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

	void VertexArray::setIndexBuffer(uint32_t id)
	{
		m_indexBufferId = id;
		glVertexArrayElementBuffer(m_rendererId, m_indexBufferId);
	}

	uint32_t VertexArray::getIndexBufferId() const
	{
		return m_indexBufferId;
	}
}
