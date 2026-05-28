#include "VertexBuffer.hpp"

#include <Scene/Mesh.hpp>

#include <glad/glad.h>

namespace Rendurr
{
	uint32_t create_vertex_buffer(const std::vector<Vertex>& vertices)
	{
		uint32_t rendererId;
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

		glCreateBuffers(1, &rendererId);
		glNamedBufferData(rendererId, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
		return rendererId;
	}

	void destroy_vertex_buffer(uint32_t rendererId)
	{
		glDeleteBuffers(1, &rendererId);
	}

	void bind_vertex_buffer(uint32_t rendererId)
	{
		glBindBuffer(GL_ARRAY_BUFFER, rendererId);
	}

	void unbind_vertex_buffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
