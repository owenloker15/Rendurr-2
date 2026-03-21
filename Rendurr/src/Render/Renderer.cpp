#include "Renderer.hpp"

#include <glad/glad.h>

namespace
{
	void drawIndexed(const Rendurr::VertexArray& vertexArray)
	{
		vertexArray.bind();
		glDrawElements(GL_TRIANGLES, vertexArray.getIndexBuffer()->getIndexCount(), GL_UNSIGNED_INT, nullptr);
		vertexArray.unbind();
	}
}

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

	void Renderer::draw(const Mesh& mesh, const glm::mat4& transform, const std::shared_ptr<Shader>& shader)
	{
		shader->use();

		MeshTransformUniform transformUniform{ transform };
		shader->uploadUniformSet(transformUniform);

		for (const auto& texture : mesh.getMaterial().getTextures())
		{
			const auto nameToSlot = Texture::TextureTypeToString(texture.getType());
			TextureUniform textureUniform{ nameToSlot.first, nameToSlot.second };
			texture.bind(nameToSlot.second);
			shader->uploadUniformSet(textureUniform);
		}

		drawIndexed(mesh.getVertexArray());
	}
}
