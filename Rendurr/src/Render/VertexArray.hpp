#pragma once
#include <memory>

#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"

namespace Rendurr
{
	class VertexArray
	{
	public:
		VertexArray();
		VertexArray(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
		~VertexArray();

		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;

		VertexArray(VertexArray&&) = default;
		VertexArray& operator=(VertexArray&&) = default;

		void bind() const;
		void unbind() const;

		void addVertexBuffer(std::unique_ptr<VertexBuffer> buffer);
		void setIndexBuffer(std::unique_ptr<IndexBuffer> buffer);
		const std::unique_ptr<IndexBuffer>& getIndexBuffer() const;
	private:
		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<IndexBuffer> m_indexBuffer;
		uint32_t m_rendererId;
	};
}
