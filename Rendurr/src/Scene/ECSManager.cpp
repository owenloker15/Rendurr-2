#include "ECSManager.hpp"

namespace Rendurr
{
	Entity ECSManager::createEntity()
	{
		return m_nextEntityId++;
	}

	void ECSManager::addComponent(Entity e, TransformComponent&& c)
	{
		m_transforms.emplace(e, std::move(c));
	}

	void ECSManager::addComponent(Entity e, MeshComponent&& c)
	{
		m_meshs.emplace(e, std::move(c));
	}

	const TransformComponent& ECSManager::getTransformComponent(Entity e)
	{
		return m_transforms.at(e);
	}

	const MeshComponent& ECSManager::getMeshComponent(Entity e)
	{
		return m_meshs.at(e);
	}
}
