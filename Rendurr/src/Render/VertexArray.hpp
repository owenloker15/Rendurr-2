#pragma once
#include <memory>

#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"

namespace Rendurr
{
	class VertexArray
	{
	public:
		VertexArray(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices);
		~VertexArray() = default;

		VertexArray(VertexArray&&) = default;
		VertexArray& operator=(VertexArray&&) = default;

		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;

		void bind() const;
		void unbind() const;
		void release();

		const IndexBuffer& getIndexBuffer() const;
	private:
		VertexBuffer m_vertexBuffer;
		IndexBuffer m_indexBuffer;
		uint32_t m_rendererId;
	};
}
