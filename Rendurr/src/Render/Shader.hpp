#pragma once

#include <filesystem>

#include "ShaderUniforms.hpp"

namespace Rendurr
{
	// TODO maybe make this a templated class
	class Shader
	{
	public:
		Shader(const std::filesystem::path& vertexFilePath, const std::filesystem::path& fragmentFilepath);

		void use();

		template <typename T>
		void uploadUniformSet(const T& uniformSet)
		{
			// Shader must be in use in order to upload a uniform to it
			use();
			uniformSet.upload(m_shaderProgramId);
		}
	private:
		uint32_t m_shaderProgramId;
	};
}
