#pragma once

#include <glm/vec4.hpp>

#include "VertexArray.hpp"

namespace Rendurr
{
	class Renderer
	{
	public:
		static void clear();
		static void setClearColor(const glm::vec4& rgba);
		static void setViewport(float width, float height);
		static void draw(const VertexArray* vertexArray);

		static void enableDebugOutput();
	};
}
