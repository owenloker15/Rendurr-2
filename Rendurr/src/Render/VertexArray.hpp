#pragma once
#include <memory>

#include "VertexBuffer.hpp"

namespace Rendurr
{
	class VertexArray
	{
	public:
		VertexArray(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
		~VertexArray();

		void bind() const;
		void unbind() const;

		void setVertexBuffer(uint32_t id);
		void setIndexBuffer(uint32_t id);

		uint32_t getIndexBufferId() const;
	private:
		uint32_t m_vertexBufferId;
		uint32_t m_indexBufferId;
		uint32_t m_rendererId;
	};
}
