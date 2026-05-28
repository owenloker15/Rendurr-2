#pragma once

#include <glm/vec4.hpp>

#include "VertexArray.hpp"
#include "Shader.hpp"

#include <Scene/Mesh.hpp>

#include "Scene/Scene.hpp"

namespace Rendurr
{
#define RENDERER_ITEM(T) \
public: \
		T(T&&) = default; \
		T& operator=(T&&) = default; \
		T(const T&) = delete; \
		T& operator=(const T&) = delete; \
		uint32_t getRendererId() const; { return m_rendererId; } \
private: \
	uint32_t m_rendererId; \

	class Renderer
	{
	public:
		static void clear();
		static void setClearColor(const glm::vec4& rgba);
		static void setViewport(float width, float height);
		static void enableDepthTesting();
		static void enableDebug();

		static void drawScene(const std::shared_ptr<Scene>& pScene, const std::shared_ptr<Shader>& pShader);
	};
}
