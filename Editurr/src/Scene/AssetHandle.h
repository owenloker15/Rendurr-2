#pragma once

#include <atomic>
#include <cstdint>

namespace Editurr
{
    typedef uint64_t AssetHandle;

    static AssetHandle INVALID_ENTITY_ID = 0;

    inline AssetHandle generate_asset_handle()
    {
        static std::atomic<AssetHandle> nextHandle{INVALID_ENTITY_ID + 1};
        return nextHandle.fetch_add(1, std::memory_order_relaxed);
    }

    inline bool is_valid_handle(const AssetHandle& handle)
    {
        return handle != INVALID_ENTITY_ID;
    }
} // namespace Editurr
