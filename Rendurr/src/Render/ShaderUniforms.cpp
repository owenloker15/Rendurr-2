#include "ShaderUniforms.hpp"

#include "Core/Log.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace 
{
	GLint getUniformLocation(uint32_t shaderId, const char* uniformName)
	{
		auto uniformLocation = glGetUniformLocation(shaderId, uniformName);
		if (uniformLocation == -1)
		{
			RND_CORE_ERROR("Failed to find uniform with name {} in shader with id {}!", uniformName, shaderId);
		}
		return uniformLocation;
	}
}

namespace Rendurr
{

	MeshUniforms::MeshUniforms(const glm::mat4& transform, uint32_t textureIndex) : m_transform(transform), m_textureIndex(textureIndex) {}

	void MeshUniforms::upload(uint32_t shaderId) const
	{
		auto transformUniformLocation = getUniformLocation(shaderId, "u_Transform");
		glUniformMatrix4fv(transformUniformLocation, 1, GL_FALSE, glm::value_ptr(m_transform));

		auto textureUniformLocation = getUniformLocation(shaderId, "u_Texture");
		glUniform1i(textureUniformLocation, m_textureIndex);
	}
}
