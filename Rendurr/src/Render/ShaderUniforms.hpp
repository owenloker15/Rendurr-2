#pragma once

#include <glm/mat4x4.hpp>

namespace Rendurr
{
	class CameraUniform
	{
	public:
		CameraUniform(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

		void upload(uint32_t shaderId) const;
	private:
		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;
	};

	class MeshUniforms
	{
	public:
		MeshUniforms(const glm::mat4& transform, uint32_t textureIndex);

		void upload(uint32_t shaderId) const;
	private:
		glm::mat4 m_transform;
		uint32_t m_textureIndex;
	};
}
