#include "EditurrLayer.hpp"

#include <Render/Renderer.hpp>

#include "glm/ext/matrix_transform.hpp"

namespace Editurr
{
	EditurrLayer::EditurrLayer(std::string name) : Layer(name)
	{
		m_shader = std::make_unique<Rendurr::Shader>("assets/shaders/vertex.glsl", "assets/shaders/frag.glsl");

		std::vector<Rendurr::Vertex> vertices = {
			{{0.5f, 0.5f, 0.0f}, {1.0f, 1.0f}},
			{{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}},
			{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}},
			{{-0.5f, 0.5f, 0.0f}, {0.0f, 1.0f}}
		};

		std::vector<uint32_t> indices = {
			0, 1, 3,
			1, 2, 3
		};

		m_vertexBuffer = std::make_unique<Rendurr::VertexBuffer>(vertices);
		m_indexBuffer = std::make_unique<Rendurr::IndexBuffer>(indices);
		m_vertexArray = std::make_unique<Rendurr::VertexArray>();
		m_vertexArray->addVertexBuffer(m_vertexBuffer.get());
		m_vertexArray->setIndexBuffer(std::move(m_indexBuffer));
		m_texture = std::make_unique<Rendurr::Texture>("assets/textures/wall.jpg");
	}

	void EditurrLayer::onAttach()
	{
	}

	void EditurrLayer::onUpdate(float dt)
	{
		Rendurr::Renderer::setViewport(800, 600);

		m_texture->bind(0);

		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, { 0.0f, 0.0f, 0.0f });
		transform = glm::rotate(transform, dt, glm::vec3(0.0f, 0.0f, 1.0f));
		Rendurr::MeshUniforms uniform = Rendurr::MeshUniforms{ transform, 0 };
		m_shader->uploadUniformSet(uniform);

		m_shader->use();
		m_vertexArray->bind();
		Rendurr::Renderer::draw(m_vertexArray.get());
		m_vertexArray->unbind();
	}
}
