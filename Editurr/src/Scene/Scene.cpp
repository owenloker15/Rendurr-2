#include "Scene.h"

namespace Editurr
{
    Entity& scene_create_entity(Scene& scene, const char* name)
    {
        Entity& e = scene.entities.emplace_back(scene.entities.size(), name);
        return e;
    }

    void scene_delete_entity(Scene& scene, uint64_t id)
    {
        std::erase_if(scene.entities, [id](const Entity& entity) {
            return entity.id == id;
        });
    }

    Entity* scene_find_entity_with_id(Scene& scene, uint64_t id)
    {
        for (auto& entity : scene.entities) {
            if (entity.id == id) {
                return &entity;
            }
        }
        return nullptr;
    }
} // namespace Editurr
