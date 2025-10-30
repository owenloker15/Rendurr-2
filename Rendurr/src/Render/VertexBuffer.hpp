#pragma once
#include <vector>

#include "glm/vec3.hpp"

namespace Rendurr
{
	struct Vertex
	{
		Vertex(glm::vec3 position) : position(position) {}
		glm::vec3 position;
	};

	class VertexBuffer
	{
	public:
		VertexBuffer(const std::vector<Vertex>& vertices);
		~VertexBuffer();

		void bind() const;
		void unbind() const;

		const unsigned int getRendererId() const;
	private:
		unsigned int m_rendererId;
	};
}
