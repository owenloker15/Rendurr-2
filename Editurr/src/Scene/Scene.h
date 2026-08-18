#pragma once

#include <vector>

#include "Entity.h"

namespace Editurr
{
    struct Scene
    {
        std::vector<Entity> entities;
    };

    Entity& scene_create_entity(Scene& scene, const char* name);

    void scene_delete_entity(Scene& scene, uint64_t id);

    Entity* scene_find_entity_with_id(Scene& scene, uint64_t id);

} // namespace Editurr
