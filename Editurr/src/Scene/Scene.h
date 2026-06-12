#pragma once

#include <vector>

#include "Entity.h"

namespace Editurr
{
    struct Scene
    {
        std::vector<Entity> entities;
    };

    Entity& scene_create_entity(Scene& scene);

} // namespace Editurr
