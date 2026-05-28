#pragma once

#include <vector>

namespace Rendurr
{
	uint32_t create_index_buffer(const std::vector<uint32_t>& indices);
	void destroy_index_buffer(uint32_t rendererId);
	uint32_t get_number_of_indices(uint32_t rendererId);
}
