#include "OrthographicProjectionStrategy.hpp"

#include "Camera.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace Rendurr
{
    glm::mat4 OrthographicProjectionStrategy::calculateViewMatrix(Camera& camera)
    {
        return glm::lookAt(camera.position, camera.target, camera.upDir);
    }

    glm::mat4 OrthographicProjectionStrategy::calculateProjectionMatrix(Camera& camera)
    {
        float left = -camera.zoom * camera.aspectRatio;
        float right = camera.zoom * camera.aspectRatio;
        float bottom = -camera.zoom;
        float top = camera.zoom;
        return glm::ortho(left, right, bottom, top, -100.0f, 100.0f);
    }
} // namespace Rendurr
