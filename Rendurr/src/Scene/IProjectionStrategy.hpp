#pragma once

#include <glm/fwd.hpp>

namespace Rendurr
{
	struct Camera;

	class IProjectionStrategy
	{
	public:
		virtual ~IProjectionStrategy() = default;

		virtual glm::mat4 calculateViewMatrix(Camera& camera) = 0;
		virtual glm::mat4 calculateProjectionMatrix(Camera& camera) = 0;
	};

}
