#include "Scene.h"

namespace Editurr
{
    Entity scene_create_entity(Scene& scene)
    {
        Entity e{.id = scene.entities.size()};
        scene.entities.emplace_back(e);
        return e;
    }

} // namespace Editurr
