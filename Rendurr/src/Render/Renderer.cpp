#include "Renderer.hpp"

#include <glad/glad.h>

#include "IndexBuffer.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "Scene/Components.hpp"

namespace
{
	void drawIndexed(const Rendurr::VertexArray& vertexArray)
	{
		vertexArray.bind();
		glDrawElements(GL_TRIANGLES, Rendurr::get_number_of_indices(vertexArray.getIndexBufferId()), GL_UNSIGNED_INT, nullptr);
		vertexArray.unbind();
	}

	void drawMesh(const Rendurr::Mesh& mesh, const std::shared_ptr<Rendurr::Shader>& pShader)
	{
		pShader->use();

		for (const auto& texture : mesh.getMaterial().getTextures())
		{
			const auto nameToSlot = Rendurr::Texture::TextureTypeToString(texture.getType());
			Rendurr::TextureUniform textureUniform{ nameToSlot.first, nameToSlot.second };
			texture.bind(nameToSlot.second);
			pShader->uploadUniformSet(textureUniform);
		}

		drawIndexed(mesh.getVertexArray());
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

	void Renderer::drawScene(const std::shared_ptr<Scene>& pScene, const std::shared_ptr<Shader>& pShader)
	{
		pShader->use();

		const auto& transforms = pScene->ecs.transforms.get_values();
		for (const auto& transformComponent : transforms)
		{
			glm::mat4 transformOut = glm::mat4(1.0f);
			transformOut = glm::translate(transformOut, transformComponent.translation);
			transformOut = glm::rotate(transformOut, glm::radians(transformComponent.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			transformOut = glm::rotate(transformOut, glm::radians(transformComponent.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			transformOut = glm::rotate(transformOut, glm::radians(transformComponent.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
			transformOut = glm::scale(transformOut, transformComponent.scale);

			MeshTransformUniform transformUniform{ transformOut };
			pShader->uploadUniformSet(transformUniform);
		}

		const auto& meshs = pScene->ecs.meshs.get_values();
		for (const auto& meshComponent : meshs)
		{
			drawMesh(meshComponent.mesh, pShader);
		}

	}
}
