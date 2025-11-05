#pragma once
#include <vector>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace Rendurr
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec2 texCoords;
	};

	class VertexBuffer
	{
	public:
		VertexBuffer(const std::vector<Vertex>& vertices);
		~VertexBuffer();

		void bind() const;
		void unbind() const;

		uint32_t getRendererId() const;
	private:
		uint32_t m_rendererId;
	};
}
