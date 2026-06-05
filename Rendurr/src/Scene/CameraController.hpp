#pragma once
#include <memory>

#include "Camera.hpp"
#include "Events/Event.hpp"
#include "IProjectionStrategy.hpp"

namespace Rendurr
{
    class CameraController
    {
    public:
        CameraController(float aspectRatio, float zoom, ProjectionType projectionType);

        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionMatrix() const;

    private:
        bool onMousePressEvent(MousePressEvent& event);
        bool onMouseReleaseEvent(MouseReleaseEvent& event);
        bool onMouseMoveEvent(MouseMoveEvent& event);
        bool onMouseScrollEvent(MouseScrollEvent& event);

    private:
        Camera m_camera;

        float m_lastMouseXPos = 0.0f;
        float m_lastMouseYPos = 0.0f;

        float m_panSensitivity = 0.005f;
        float m_rotateSensitivity = 0.025f;
        float m_zoomSensitivity = 0.25f;

        bool m_panning = false;
        bool m_rotating = false;
    };
} // namespace Rendurr
