#pragma once

#include "IProjectionStrategy.hpp"

namespace Rendurr
{
	class OrthographicProjectionStrategy : public IProjectionStrategy
	{
	public:
		glm::mat4 calculateViewMatrix(Camera& camera) override;
		glm::mat4 calculateProjectionMatrix(Camera& camera) override;
	};
}
