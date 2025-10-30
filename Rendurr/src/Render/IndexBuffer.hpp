#pragma once

#include <vector>

namespace Rendurr
{
	class IndexBuffer
	{
	public:
		IndexBuffer(const std::vector<uint32_t>& indices);
		~IndexBuffer();

		void bind() const;
		void unbind() const;

		uint32_t getRendererId() const;
		uint32_t getIndexCount() const;
	private:
		uint32_t m_rendererId;
		uint32_t m_indexCount;
	};
}
