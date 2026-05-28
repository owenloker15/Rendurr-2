#include "ECSManager.hpp"

namespace Rendurr
{
	EntityHandle create_entity(EcsManager& ecs)
	{
		return ecs.nextEntityId++;
	}

	void destroy_entity(EcsManager& ecs, EntityHandle e)
	{
		ecs.transforms.remove(e);
	}
}
