#pragma once
#include <filesystem>

namespace Editurr
{
    namespace Utils
    {
        std::filesystem::path getExecutablePath();
        std::filesystem::path getAssetDirectory();
    } // namespace Utils
} // namespace Editurr
