#include "Renderer.hpp"

#include <iostream>
#include <glad/glad.h>

namespace Rendurr
{
	void Renderer::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::setClearColor(const glm::vec4& rgba)
	{
		glClearColor(rgba.r, rgba.g, rgba.b, rgba.a);
	}

	void Renderer::setViewport(float width, float height)
	{
		glViewport(0, 0, width, height);
	}

	void Renderer::enableDepthTesting()
	{
		glEnable(GL_DEPTH_TEST);
	}

	void Renderer::draw(const VertexArray* vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getIndexCount(), GL_UNSIGNED_INT, nullptr);
	}
}
