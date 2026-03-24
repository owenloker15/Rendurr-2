#pragma once


#include "ComponentPool.hpp"
#include "Entity.hpp"

#include "Core/Log.hpp"

#include <array>
#include <unordered_set>

namespace Rendurr
{
	constexpr inline uint32_t MAX_COMPONENTS = 32;

	class ECSManager
	{
	public:
		ECSManager() = default;
		~ECSManager() = default;

		Entity createEntity();

		const std::unordered_set<Entity>& getEntities() const;

		template <typename T>
		bool registerComponent()
		{
			ComponentType type = GetComponentTypeID<T>();
			
			if (m_componentPools.at(type) != nullptr)
			{
				RND_CORE_ERROR("Component already registered!");
				return false;
			}

			m_componentPools[type] = std::make_unique<ComponentPool<T>>();
			return true;
		}

		template<typename T>
		void addComponent(Entity entity, T&& component)
		{
			getPool<T>().add(entity, std::forward<T>(component));
		}

		template<typename T>
		void removeComponent(Entity entity)
		{
			 getPool<T>().remove(entity);
		}

		template <typename T>
		bool hasComponent(Entity entity) const
		{
			return getPool<T>().has(entity);

		}

		template <typename T>
		[[nodiscard]] T* getComponent(Entity entity)
		{
			return getPool<T>().get(entity);
		}

		template <typename T>
		[[nodiscard]] const T* getComponent(Entity entity) const
		{
			return getPool<T>().get(entity);
		}

	private:

		using ComponentType = uint16_t;

		static ComponentType GetUniqueComponentTypeID()
		{
			static ComponentType id = 0;
			return id++;
		}

		template<typename T>
		static ComponentType GetComponentTypeID()
		{
			static ComponentType id = GetUniqueComponentTypeID();
			return id;
		}
	
		template<typename T>
		ComponentPool<T>& getPool() const
		{
			return *static_cast<ComponentPool<T>*>((m_componentPools.at(GetComponentTypeID<T>()).get()));
		}

		std::unordered_set<Entity> m_entities;
		std::array<std::unique_ptr<IComponentPool>, MAX_COMPONENTS> m_componentPools;
	};
}
