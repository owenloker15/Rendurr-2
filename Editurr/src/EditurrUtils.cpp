#include "EditurrUtils.hpp"

#if defined(_WIN32)
#include <windows.h>
#endif

namespace Editurr
{
	namespace Utils
	{
		std::filesystem::path getExecutablePath()
		{
#if defined(_WIN32)

			char buffer[MAX_PATH];
			GetModuleFileNameA(NULL, buffer, MAX_PATH);
			return std::filesystem::path(buffer);
#else
#error Unsupported platform
#endif
		}

		std::filesystem::path getAssetDirectory()
		{
			auto exe = getExecutablePath();
			return exe.parent_path() / "assets";
		}
	}
}
