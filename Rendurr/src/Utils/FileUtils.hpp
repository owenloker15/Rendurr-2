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
            std::ifstream file(filepath.string(), std::ios::binary);
            if (!file) {
                RND_CORE_ERROR("Failed to open file: {}", filepath.string());
                return "";
            }

            if (!file.is_open()) {
                RND_CORE_ERROR("Stream failed to open: {}", filepath.string());
                return "";
            }

            std::ostringstream buffer;
            buffer << file.rdbuf();

            file.close();

            return buffer.str();
        }
    } // namespace Utils
} // namespace Rendurr
