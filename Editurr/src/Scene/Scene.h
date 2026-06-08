#pragma once

#include <cstdint>

#include "ECSManager.h"

namespace Editurr
{
    class Scene
    {
    public:
        Scene() = default;

        uint32_t createEntity();

        template <typename T>
        void addComponent(Entity e, T&& c)
        {
            m_ecs.addComponent(e, std::forward<T>(c));
        }

        const TransformComponent& getTransformComponent(Entity e) const
        {
            return m_ecs.getTransformComponent(e);
        }

        const MeshComponent& getMeshComponent(Entity e) const
        {
            return m_ecs.getMeshComponent(e);
        }

        template <typename Func>
        void forEachEntity(Func&& f) const
        {
            for (size_t i = 0; i < m_ecs.m_nextEntityId; i++) {
                f(i);
            }
        }

    private:
        ECSManager m_ecs;
    };
} // namespace Editurr
