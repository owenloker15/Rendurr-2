#include "Camera.hpp"

#include <glm/ext/matrix_transform.hpp>

namespace Rendurr
{
	Camera::Camera(const glm::vec3& initialPosition, const glm::vec3& initialTarget) : m_position(initialPosition), m_target(initialTarget)
	{
		
	}

	glm::mat4 Camera::calculateViewMatrix()
	{
		// auto cameraLookAtDir = glm::normalize(m_target - m_position);
		// auto rightLookAt = glm::normalize(glm::cross(m_upDir, cameraLookAtDir));
		// auto upLookAt = glm::normalize(glm::cross(cameraLookAtDir, rightLookAt));
		glm::mat4 viewMatrix = glm::lookAt(m_position, m_target, m_upDir);
		return viewMatrix;
	}

	glm::mat4 Camera::calculateProjectionMatrix()
	{
	}

	glm::mat4 Camera::calculateViewProjectionMatrix()
	{
	}
}
