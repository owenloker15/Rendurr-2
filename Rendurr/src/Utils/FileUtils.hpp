#pragma once

#include <filesystem>
#include <fstream>

#include "Core/Log.hpp"

namespace Rendurr
{
    namespace Utils
    {
        inline std::string read_file(const std::string& path)
        {
            std::ifstream f(path, std::ios::binary | std::ios::ate);
            if (!f) {
                RND_CORE_ERROR("Failed to open file: {}", path);
                return "";
            }
            std::string s(f.tellg(), '\0');

            f.seekg(0);
            f.read(s.data(), s.size());
            return s;
        }
    } // namespace Utils
} // namespace Rendurr
