#pragma once

#include <array>
#include <unordered_set>

#include "ComponentPool.h"
#include "Components.h"
#include "Core/Log.h"
#include "Entity.h"

namespace Editurr
{
    constexpr inline uint32_t MAX_COMPONENTS = 32;

    class ECSManager
    {
    public:
        ECSManager() = default;
        ~ECSManager() = default;

        ECSManager(const ECSManager&) = delete;
        ECSManager& operator=(const ECSManager&) = delete;

        ECSManager(ECSManager&&) = default;
        ECSManager& operator=(ECSManager&&) = default;

        Entity createEntity();

        void addComponent(Entity e, TransformComponent&& c);
        void addComponent(Entity e, MeshComponent&& c);

        const TransformComponent& getTransformComponent(Entity e) const;
        const MeshComponent& getMeshComponent(Entity e) const;

        uint32_t m_nextEntityId = 0;

    private:
        std::unordered_map<Entity, TransformComponent> m_transforms{};
        std::unordered_map<Entity, MeshComponent> m_meshs{};
    };
} // namespace Editurr
