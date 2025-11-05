#pragma once

#include <chrono>

namespace Rendurr
{
	std::chrono::time_point<std::chrono::high_resolution_clock> getTime()
	{
		return std::chrono::high_resolution_clock::now();
	}
}
