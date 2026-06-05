#pragma once

#include <array>
#include <cstdint>

template <typename T, uint32_t size>
class SparseSet
{
public:
    SparseSet() = default;
    ~SparseSet() = default;

    bool empty() const
    {
        return !m_size;
    }

private:
    uint32_t m_size = 0;
    std::array<T, size> m_sparse{};
    std::array<T, size> m_dense{};
};