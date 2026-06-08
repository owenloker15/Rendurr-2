#pragma once

#include <cstdint>
#include <glm/vec3.hpp>
#include <string>

#include "Mesh.h"

namespace Editurr
{
    // Components
    struct TagComponent
    {
        TagComponent(uint32_t id, std::string name) : id(id), name(std::move(name)) {}

        uint32_t id;
        std::string name;
    };

    struct TransformComponent
    {
        TransformComponent(const glm::vec3& translation,
                           const glm::vec3& rotation,
                           const glm::vec3& scale)
            : translation(translation), rotation(rotation), scale(scale)
        {}

        glm::vec3 translation = {0.0f, 0.0f, 0.0f};
        glm::vec3 rotation = {0.0f, 0.0f, 0.0f}; // In degrees
        glm::vec3 scale = {1.0f, 1.0f, 1.0f};
    };

    struct MeshComponent
    {
        explicit MeshComponent(AssetHandle handle) : handle(handle) {}

        AssetHandle handle;
    };
} // namespace Editurr
