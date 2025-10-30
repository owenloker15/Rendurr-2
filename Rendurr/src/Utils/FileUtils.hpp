#pragma once

#include <filesystem>
#include <fstream>

#include "Core/Log.hpp"

namespace Rendurr
{
	namespace Utils
	{
		inline std::string readFileTextContents(const std::filesystem::path& filepath)
		{
			std::ifstream filestream(filepath, std::ios::in);
			if (!filestream)
			{
				RND_CORE_ERROR("Failed to open file: {}", filepath.string());
				return "";
			}

			std::ostringstream buffer;
			buffer << filestream.rdbuf();

			filestream.close();

			return buffer.str();
		}
	}
}
