#include "Scene.h"

namespace Editurr
{
    uint32_t Scene::createEntity()
    {
        return m_ecs.createEntity();
    }

} // namespace Editurr
