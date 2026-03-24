#include "ECSManager.hpp"

namespace Rendurr
{
	Entity ECSManager::createEntity()
	{
		const uint32_t id = m_entities.size();
		if (m_entities.contains(id))
		{
			RND_CORE_ERROR("Entity with id already exists! This should not be possible");
		}
		m_entities.insert(id);
		return id;
	}

	const std::unordered_set<Entity>& ECSManager::getEntities() const
	{
		return m_entities;
	}
}
