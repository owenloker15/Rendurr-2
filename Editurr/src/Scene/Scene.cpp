#include "Scene.h"

namespace Editurr
{
    Entity& scene_create_entity(Scene& scene)
    {
        Entity& e = scene.entities.emplace_back(scene.entities.size());
        return e;
    }

} // namespace Editurr
