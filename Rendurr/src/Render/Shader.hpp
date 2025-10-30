#pragma once

#include <filesystem>

namespace Rendurr
{
	class Shader
	{
	public:
		Shader(const std::filesystem::path& vertexFilePath, const std::filesystem::path& fragmentFilepath);

		void use();
	private:
		unsigned int m_shaderProgramId;
	};
}
