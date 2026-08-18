#pragma once

#include <glm/vec3.hpp>

#include "AssetManager.h"

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
        const char* name;
        AssetHandle model = INVALID_ENTITY_ID;
        Transform transform;
    };
} // namespace Editurr
