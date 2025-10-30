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
		~VertexArray();

		void bind() const;
		void unbind() const;

		void addVertexBuffer(const VertexBuffer* buffer);
		void setIndexBuffer(std::unique_ptr<IndexBuffer> buffer);
		const std::unique_ptr<IndexBuffer>& getIndexBuffer() const;
	private:
		unsigned int m_rendererId;
		std::unique_ptr<IndexBuffer> m_indexBuffer;
	};
}
