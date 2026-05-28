#pragma once
#include <vector>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace Rendurr
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
	};

	uint32_t create_vertex_buffer(const std::vector<Vertex>& vertices);
	void destroy_vertex_buffer(uint32_t rendererId);
	void bind_vertex_buffer(uint32_t rendererId);
	void unbind_vertex_buffer();

}
