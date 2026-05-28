#include "IndexBuffer.hpp"

#include <glad/glad.h>

namespace Rendurr
{
	uint32_t create_index_buffer(const std::vector<uint32_t>& indices)
	{
		uint32_t rendererId;

		glCreateBuffers(1, &rendererId);
		glNamedBufferData(rendererId, sizeof(uint32_t) * indices.size(), indices.data(), GL_STATIC_DRAW);
		return rendererId;
	}

	void destroy_index_buffer(uint32_t rendererId)
	{
		glDeleteBuffers(1, &rendererId);
	}

	uint32_t get_number_of_indices(uint32_t rendererId)
	{
		GLint sizeInBytes = 0;

		glGetNamedBufferParameteriv(rendererId,
									GL_BUFFER_SIZE,
									&sizeInBytes);

		uint32_t indexCount = static_cast<uint32_t>(
			sizeInBytes / sizeof(uint32_t)
		);
		return indexCount;
	}
}
