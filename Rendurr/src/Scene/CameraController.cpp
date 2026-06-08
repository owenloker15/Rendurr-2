#include "CameraController.hpp"

#include "Core/Log.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace Rendurr
{
    CameraController::CameraController(float aspectRatio, float zoom, ProjectionType projectionType)
        : m_camera{.position = {0, 0, 5},
                   .target = {0, 0, 0},
                   .aspectRatio = aspectRatio,
                   .zoom = zoom,
                   .projType = projectionType}

    {}

    void CameraController::update(const Input& input)
    {
        const float deltaX = input.deltaX;
        const float deltaY = input.deltaY;

        // Pan
        if (is_mouse_down(input, Key::ButtonMiddle)) {
            const glm::vec3 cameraDirection = glm::normalize(m_camera.target - m_camera.position);

            const glm::vec3 right = glm::normalize(glm::cross(cameraDirection, m_camera.upDir));

            const glm::vec3 up = m_camera.upDir;

            const glm::vec3 offset =
                (deltaX * m_panSensitivity * right) + (deltaY * m_panSensitivity * up);

            m_camera.position += offset;
            m_camera.target += offset;
        }

        // Orbit
        if (is_mouse_down(input, Key::ButtonLeft)) {
            const float yaw = -deltaX * m_rotateSensitivity;
            const float pitch = -deltaY * m_rotateSensitivity;

            glm::vec3 offset = m_camera.position - m_camera.target;

            const float distance = glm::length(offset);
            offset = glm::normalize(offset);

            // Yaw around world up
            const glm::mat4 yawRotation = glm::rotate(glm::mat4(1.0f), yaw, m_camera.upDir);

            offset = glm::vec3(yawRotation * glm::vec4(offset, 0.0f));

            // Right axis after yaw
            const glm::vec3 right = glm::normalize(glm::cross(m_camera.upDir, offset));

            // Pitch around camera right
            const glm::mat4 pitchRotation = glm::rotate(glm::mat4(1.0f), pitch, right);

            offset = glm::vec3(pitchRotation * glm::vec4(offset, 0.0f));

            m_camera.position = m_camera.target + offset * distance;
        }

        // Zoom
        m_camera.zoom -= input.scrollDeltaY * m_zoomSensitivity;
        m_camera.zoom = glm::max(m_camera.zoom, 0.01f);

        m_lastMouseXPos = input.mouseXPos;
        m_lastMouseYPos = input.mouseYPos;
    }

    glm::mat4 CameraController::getViewMatrix() const
    {
        switch (m_camera.projType) {
            case ProjectionType::Ortho:
                {
                    return glm::lookAt(m_camera.position, m_camera.target, m_camera.upDir);
                }

            case ProjectionType::Perspective:
                {
                    RND_ASSERT(false, "Perspective projection not supported");
                    return glm::mat4(1.0f);
                }

            default:
                {
                    RND_ASSERT(false, "Unknown projection type");
                    return glm::mat4(1.0f);
                }
        }
    }

    glm::mat4 CameraController::getProjectionMatrix() const
    {
        switch (m_camera.projType) {
            case ProjectionType::Ortho:
                {
                    const float halfW = m_camera.zoom * m_camera.aspectRatio;
                    const float halfH = m_camera.zoom;
                    return glm::ortho(-halfW, halfW, -halfH, halfH, -100.0f, 100.0f);
                }
            case ProjectionType::Perspective:
                {
                    RND_ASSERT(false, "Perspective projection not supported");
                    return glm::mat4(1.0f);
                }
            default:
                {
                    RND_ASSERT(false, "Unknown projection type");
                    return glm::mat4(1.0f);
                }
        }
    }

} // namespace Rendurr
