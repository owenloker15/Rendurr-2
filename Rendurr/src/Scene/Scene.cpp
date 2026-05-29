#include "Scene.hpp"

namespace Rendurr
{
    uint32_t Scene::createEntity()
    {
        return m_ecs.createEntity();
    }

} // namespace Rendurr
