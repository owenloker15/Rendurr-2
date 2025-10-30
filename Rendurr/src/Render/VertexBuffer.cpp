#include "VertexBuffer.hpp"

#include <glad/glad.h>

namespace Rendurr
{

	VertexBuffer::VertexBuffer(const std::vector<Vertex>& vertices)
	{
		/*
		// Create a buffer object
		glGenBuffers(1, &m_rendererId);

		// Bind the array buffer to the GL_ARRAY_BUFFER target in the opengl context
		// Any calls to the GL_ARRAY_BUFFER	target will be called on the currently bound buffer, m_rendererId
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);

		// Copies the vertices into the currently bound GL_ARRAY_BUFFER target, m_rendererId
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

		// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, )
		*/

		glCreateBuffers(1, &m_rendererId);
		glNamedBufferData(m_rendererId, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_rendererId);
	}

	void VertexBuffer::bind() const
	{
		// glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
	}

	void VertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	const unsigned int VertexBuffer::getRendererId() const
	{
		return m_rendererId;
	}
}
