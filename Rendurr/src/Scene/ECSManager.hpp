#pragma once
#include "Components.hpp"
#include "Entity.hpp"

#include "Utils/SparseSet.h"

namespace Rendurr
{
	struct EcsManager
	{
		EcsManager() :
		               transforms(MAX_ENTITIES),
		               meshs(MAX_ENTITIES)
		{
		}

		uint32_t nextEntityId = 0;

		// Components
		SparseSet<TransformComponent> transforms;
		SparseSet<MeshComponent> meshs;
	};

	EntityHandle create_entity(EcsManager &ecs);
	void destroy_entity(EcsManager &ecs, EntityHandle e);

	inline void add_component(EcsManager &ecs, EntityHandle e, TransformComponent c)
	{
		ecs.transforms.insert(e, std::move(c));
	}

	inline void add_component(EcsManager &ecs, EntityHandle e, MeshComponent c)
	{
		ecs.meshs.insert(e, std::move(c));
	}
}
