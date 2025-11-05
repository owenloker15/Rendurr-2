#include "Shader.hpp"

#include <glad/glad.h>

#include "Utils/FileUtils.hpp"

namespace
{
	uint32_t compileShader(GLenum shaderType, const std::string& shaderSource)
	{
		// Create shader object
		uint32_t shader = glCreateShader(shaderType);

		// Attach the shader source to the shader object and compile the shader
		const char* shaderCStr = shaderSource.c_str();
		glShaderSource(shader, 1, &shaderCStr, NULL);
		glCompileShader(shader);

		// Check for errors
		int  success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			RND_CORE_ERROR("Shader compilation failed!", infoLog);
		}

		return shader;

	}
}

namespace Rendurr
{
	Shader::Shader(const std::filesystem::path& vertexFilePath, const std::filesystem::path& fragmentFilepath)
	{
		std::string vertexShaderContent = Utils::readFileTextContents(vertexFilePath);
		std::string fragmentShaderContent = Utils::readFileTextContents(fragmentFilepath);

		// Compile vertex and fragment shaders
		uint32_t vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderContent);
		uint32_t fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderContent);

		// Link the compiled shaders to the shader program
		m_shaderProgramId = glCreateProgram();
		glAttachShader(m_shaderProgramId, vertexShader);
		glAttachShader(m_shaderProgramId, fragmentShader);
		glLinkProgram(m_shaderProgramId);

		// Check for errors
		int  success;
		char infoLog[512];
		glGetProgramiv(m_shaderProgramId, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_shaderProgramId, 512, NULL, infoLog);
			RND_CORE_ERROR("Failed to link shader program!", infoLog);
		}

		// Cleanup shaders since they are already linked to the shader program
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Shader::use()
	{
		glUseProgram(m_shaderProgramId);
	}

}
