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

	class VertexBuffer
	{
	public:
		VertexBuffer(std::vector<Vertex>&& vertices);
		~VertexBuffer() = default;

		void release();

		uint32_t getRendererId() const;
	private:
		uint32_t m_rendererId;
	};
}
