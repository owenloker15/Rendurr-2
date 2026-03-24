#pragma once

#include "ECSManager.hpp"

#include <cstdint>

namespace Rendurr
{
	class Scene
	{
	public:
		Scene() = default;

		uint32_t createEntity();

		template <typename T>
		bool registerComponent()
		{
			return m_ecs.registerComponent<T>();
		}

		template<typename T>
		void addComponent(Entity entity, T&& component)
		{
			return m_ecs.addComponent(entity, std::forward<T>(component));
		}

		template<typename T>
		void removeComponent(Entity entity)
		{
			return m_ecs.removeComponent<T>(entity);
		}

		template <typename T>
		bool hasComponent(Entity entity) const
		{
			return m_ecs.hasComponent<T>(entity);
		}

		template <typename T>
		[[nodiscard]] T* getComponent(Entity entity)
		{
			return m_ecs.getComponent<T>(entity);
		}

		template <typename T>
		[[nodiscard]] const T* getComponent(Entity entity) const
		{
			return m_ecs.getComponent<T>(entity);
		}

		void forEachEntity(const std::function<void(const Entity&)>& func) const
		{
			for (const auto& entity : m_ecs.getEntities())
			{
				func(entity);
			}
		}
	private:
		ECSManager m_ecs;
	};
}
