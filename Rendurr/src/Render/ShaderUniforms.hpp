#pragma once

#include <glm/mat4x4.hpp>

namespace Rendurr
{
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
