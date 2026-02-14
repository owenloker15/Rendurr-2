#include "CameraController.hpp"

#include "Core/Log.hpp"
#include "Events/EventPublisher.hpp"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace Rendurr
{
	CameraController::CameraController(double aspectRatio, double zoom, std::unique_ptr<IProjectionStrategy> projectionStrategy) : m_camera(aspectRatio, zoom, { 0, 0, 1 }, { 0, 0, 0 }), m_strategy(std::move(projectionStrategy)){
		EventPublisher::getInstance()->subscribe<MousePressEvent>(this, &CameraController::onMousePressEvent);
		EventPublisher::getInstance()->subscribe<MouseReleaseEvent>(this, &CameraController::onMouseReleaseEvent);
		EventPublisher::getInstance()->subscribe<MouseMoveEvent>(this, &CameraController::onMouseMoveEvent);
	}

	glm::mat4 CameraController::getViewMatrix()
	{
		if (!m_strategy)
		{
			RND_CORE_ERROR("No projection strategy set!");
			return {};
		}

		return m_strategy->calculateViewMatrix(m_camera);
	}

	glm::mat4 CameraController::getProjectionMatrix()
	{
		if (!m_strategy)
		{
			RND_CORE_ERROR("No projection strategy set!");
			return {};
		}

		return m_strategy->calculateProjectionMatrix(m_camera);
	}

	bool CameraController::onMousePressEvent(MousePressEvent& event)
	{
		const auto mouseButton = event.getButton();
		switch (mouseButton)
		{
		case Key::ButtonMiddle:
			m_panning = true;
			break;
		case Key::ButtonLeft:
			m_rotating = true;
			break;
		}
		return true;
	}

	bool CameraController::onMouseReleaseEvent(MouseReleaseEvent& event)
	{
		const auto mouseButton = event.getButton();
		switch (mouseButton)
		{
		case Key::ButtonMiddle:
			m_panning = false;
			break;
		case Key::ButtonLeft:
			m_rotating = false;
			break;
		}
		return true;
	}

	bool CameraController::onMouseMoveEvent(MouseMoveEvent& event)
	{
		const float xPos = event.getXPos();
		const float yPos = event.getYPos();

		const float deltaX = xPos - m_lastMouseXPos;
		const float deltaY = yPos - m_lastMouseYPos;

		if (m_panning)
		{
			// Final - initial (target - position)
			const glm::vec3 cameraDirection = m_camera.target - m_camera.position;

			// Normal of the cross of the up direction and direction camera is facing
			const glm::vec3 right = glm::normalize(glm::cross(m_camera.upDir, cameraDirection));
			const glm::vec3 up = m_camera.upDir;

			const glm::vec3 offset = (deltaX * m_panSensitivity * right) + (deltaY * m_panSensitivity * up);
			m_camera.position += offset;
			m_camera.target += offset;
		}

		if (m_rotating)
		{
			const float yaw = deltaX * m_rotateSensitivity;
			const float pitch = deltaY * m_rotateSensitivity;

			// Final - initial (target - position)
			glm::vec3 direction = glm::normalize(m_camera.position - m_camera.target);

			glm::mat4 yawRotation = glm::rotate(glm::mat4(1.0f), yaw, m_camera.upDir);
			direction = glm::vec3(yawRotation * glm::vec4(direction, 1.0f));

			glm::vec3 right = glm::normalize(glm::cross(m_camera.upDir, direction));
			glm::mat4 pitchRotation = glm::rotate(glm::mat4(1.0f), pitch, right);
			direction = glm::vec3(pitchRotation * glm::vec4(direction, 1.0f));

			m_camera.position = m_camera.target + direction * glm::length(m_camera.position - m_camera.target);
		}

		m_lastMouseXPos = xPos;
		m_lastMouseYPos = yPos;

		return true;
	}
}
