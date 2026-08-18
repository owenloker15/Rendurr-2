#include "Scene.h"

namespace Editurr
{
    Entity& scene_create_entity(Scene& scene, const char* name)
    {
        Entity& e = scene.entities.emplace_back(scene.entities.size(), name);
        return e;
    }

    std::optional<Entity> scene_find_entity_with_id(Scene& scene, uint64_t id)
    {
        for (const auto& entity : scene.entities) {
            if (entity.id == id) {
                return entity;
            }
        }
        return std::nullopt;
    }
} // namespace Editurr
