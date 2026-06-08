#pragma once

#include <bitset>
#include <unordered_map>

#include "Core/Log.h"
#include "Entity.h"

namespace Editurr
{
    class IComponentPool
    {
    public:
        virtual ~IComponentPool() = default;
    };

    template <typename T>
    class ComponentPool : public IComponentPool
    {
    public:
        ComponentPool() = default;

        void add(Entity entity, T&& component)
        {
            m_components[entity] = std::forward<T>(component);
            m_hasComponent.set(entity);
        }

        void remove(Entity entity)
        {
            if (m_hasComponent[entity]) {
                m_hasComponent.reset(entity);
            }
            else {
                RND_CORE_ASSERT(false, "Attempting to remove component that does not exist");
            }
        }

        bool has(Entity entity) const
        {
            return m_hasComponent[entity];
        }

        [[nodiscard]] T* get(Entity entity)
        {
            return &m_components[entity];
        }

        [[nodiscard]] const T* get(Entity entity) const
        {
            return &m_components[entity];
        }

    private:
        std::array<T, MAX_ENTITIES> m_components;
        std::bitset<MAX_ENTITIES> m_hasComponent;
    };
} // namespace Editurr
