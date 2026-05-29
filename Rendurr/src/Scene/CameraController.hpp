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
        CameraController(double aspectRatio,
                         double zoom,
                         std::unique_ptr<IProjectionStrategy> projectionStrategy);

        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();

    private:
        bool onMousePressEvent(MousePressEvent& event);
        bool onMouseReleaseEvent(MouseReleaseEvent& event);
        bool onMouseMoveEvent(MouseMoveEvent& event);
        bool onMouseScrollEvent(MouseScrollEvent& event);

    private:
        std::unique_ptr<IProjectionStrategy> m_strategy;
        Camera m_camera;

        bool m_panning = false;
        bool m_rotating = false;

        float m_lastMouseXPos = 0.0f;
        float m_lastMouseYPos = 0.0f;

        float m_panSensitivity = 0.005f;
        float m_rotateSensitivity = 0.025;
        float m_zoomSensitivity = 0.25f;
    };
} // namespace Rendurr
