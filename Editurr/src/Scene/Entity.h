#pragma once

#include "AssetManager.h"
#include "glm/vec3.hpp"

namespace Editurr
{
#define MAX_ENTITIES 1024

    struct Transform
    {
        glm::vec3 translation = {0.0f, 0.0f, 0.0f};
        glm::vec3 rotation = {0.0f, 0.0f, 0.0f}; // In degrees
        glm::vec3 scale = {1.0f, 1.0f, 1.0f};
    };

    struct Entity
    {
        uint64_t id;
        AssetHandle model;
        Transform transform;
    };
} // namespace Editurr
