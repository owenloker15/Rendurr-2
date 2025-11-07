#pragma once

#include <glm/vec3.hpp>

#include <glm/fwd.hpp>

namespace Rendurr
{
	class Camera
	{
	public:
		Camera(const glm::vec3& initialPosition, const glm::vec3& initialTarget);
		~Camera() = default;

		glm::mat4 calculateViewMatrix();
		glm::mat4 calculateProjectionMatrix();
		glm::mat4 calculateViewProjectionMatrix();
	private:
		glm::vec3 m_position;
		glm::vec3 m_target;

		glm::vec3 m_upDir{ 0.0f, 1.0f, 0.0f };
	};
}
