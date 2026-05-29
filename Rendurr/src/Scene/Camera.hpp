#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace Rendurr
{
    struct Camera
    {
        double aspectRatio;
        double zoom;

        glm::vec3 position;
        glm::vec3 target;

        glm::vec3 upDir{0.0f, 1.0f, 0.0f};
    };
} // namespace Rendurr
