#include "Renderer.hpp"

#include <glad/glad.h>

#include "glm/ext/matrix_transform.hpp"
#include "Scene/Components.hpp"

namespace
{
	void drawIndexed(const Rendurr::VertexArray& vertexArray)
	{
		vertexArray.bind();
		glDrawElements(GL_TRIANGLES, vertexArray.getIndexBuffer()->getIndexCount(), GL_UNSIGNED_INT, nullptr);
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

		pScene->forEachEntity([&pScene, &pShader](Entity entity)
			{
				if (pScene->hasComponent<TransformComponent>(entity))
				{
					const auto transformComponent = pScene->getComponent<TransformComponent>(entity);
					glm::mat4 transform = glm::mat4(1.0f);
					transform = glm::translate(transform, transformComponent->translation);
					transform = glm::rotate(transform, glm::radians(transformComponent->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
					transform = glm::rotate(transform, glm::radians(transformComponent->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
					transform = glm::rotate(transform, glm::radians(transformComponent->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
					transform = glm::scale(transform, transformComponent->scale);

					MeshTransformUniform transformUniform{ transform };
					pShader->uploadUniformSet(transformUniform);

				}

				if (pScene->hasComponent<MeshComponent>(entity))
				{
					const auto meshComponent = pScene->getComponent<MeshComponent>(entity);
					drawMesh(meshComponent->mesh, pShader);
				}
			});
	}
}
