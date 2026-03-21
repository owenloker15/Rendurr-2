#pragma once

#include <string>
#include <glm/mat4x4.hpp>

namespace Rendurr
{
	class CameraUniform
	{
	public:
		CameraUniform(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

		void upload(uint32_t shaderId) const;
	private:
		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;
	};

	class MeshTransformUniform
	{
	public:
		MeshTransformUniform(glm::mat4 transform);

		void upload(uint32_t shaderId) const;
	private:
		glm::mat4 m_transform;
	};

	class TextureUniform
	{
	public:
		TextureUniform(std::string uniformName, uint32_t textureSlot);

		void upload(uint32_t shaderId) const;
	private:
		std::string m_uniformName;
		uint32_t m_textureSlot;
	};
}
