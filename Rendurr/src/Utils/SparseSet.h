#pragma once
#include <cstdint>
#include <vector>

namespace Rendurr
{
	template <typename T>
	class SparseSet {

public:
    explicit SparseSet(size_t max_id) {
        sparse.resize(max_id, -1);
    }

    // O(1) Add or Update
    void insert(int id, T value) {
        if (contains(id)) {
            values[sparse[id]] = value;
            return;
        }
        sparse[id] = size;
        dense_id.push_back(id);
        values.push_back(value);
        size++;
    }

    // O(1) Lookup
    bool contains(int id) const {
        return id < sparse.size() && sparse[id] != -1;
    }

    // O(1) Removal (Swap-and-Pop)
    void remove(int id) {
        if (!contains(id)) return;

        int index_to_remove = sparse[id];
        int last_id = dense_id.back();

        // Swap with the last element to keep dense array contiguous
        values[index_to_remove] = values.back();
        dense_id[index_to_remove] = last_id;
        sparse[last_id] = index_to_remove;

        // Cleanup
        values.pop_back();
        dense_id.pop_back();
        sparse[id] = -1;
        size--;
    }


    // Fast contiguous iteration
    const std::vector<T>& get_values() const { return values; }
	private:
		std::vector<uint32_t> sparse;   // Maps ID -> Index in dense
		std::vector<uint32_t> dense_id; // Maps Index -> ID
		std::vector<T> values; // Contiguous values
		uint32_t size = 0;                 // Number of elements
};}
