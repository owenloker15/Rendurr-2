#pragma once

#include <vector>

namespace Rendurr
{
    class IndexBuffer
    {
    public:
        IndexBuffer(std::vector<uint32_t>&& indices);
        ~IndexBuffer() = default;

        void release();

        uint32_t getRendererId() const;
        uint32_t getIndexCount() const;

    private:
        uint32_t m_rendererId;
        uint32_t m_indexCount;
    };
} // namespace Rendurr
