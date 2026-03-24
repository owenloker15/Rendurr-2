#pragma once

#include <glm/vec4.hpp>

#include "VertexArray.hpp"
#include "Shader.hpp"

#include <Scene/Mesh.hpp>

#include "Scene/Scene.hpp"

namespace Rendurr
{
	class Renderer
	{
	public:
		static void clear();
		static void setClearColor(const glm::vec4& rgba);
		static void setViewport(float width, float height);
		static void enableDepthTesting();

		static void drawScene(const std::shared_ptr<Scene>& pScene, const std::shared_ptr<Shader>& pShader);
	};
}
