#include "EditurrLayer.hpp"

#include <Render/Renderer.hpp>

#include "glm/ext/matrix_transform.hpp"
#include "Scene/OrthographicProjectionStrategy.hpp"

namespace Editurr
{
	EditurrLayer::EditurrLayer(std::string name) : m_cameraController(1280.0 / 720, 5.0, std::make_unique<Rendurr::OrthographicProjectionStrategy>()), Layer(name)
	{
		m_shader = std::make_unique<Rendurr::Shader>("assets/shaders/vertex.glsl", "assets/shaders/frag.glsl");

std::vector<Rendurr::Vertex> vertices = {
    // Front face
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}},
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f}},

    // Back face
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
    {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}},

    // Left face
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}},
    {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}},
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}},

    // Right face
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f}},

    // Top face
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}},

    // Bottom face
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f}},
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f}},
};

std::vector<uint32_t> indices = {
    0, 1, 2, 2, 3, 0,       // Front
    4, 5, 6, 6, 7, 4,       // Back
    8, 9,10,10,11, 8,       // Left
   12,13,14,14,15,12,       // Right
   16,17,18,18,19,16,       // Top
   20,21,22,22,23,20        // Bottom
};

		auto vertexBuffer = std::make_unique<Rendurr::VertexBuffer>(vertices);
		auto indexBuffer = std::make_unique<Rendurr::IndexBuffer>(indices);

		m_vertexArray = std::make_unique<Rendurr::VertexArray>();
		m_vertexArray->addVertexBuffer(std::move(vertexBuffer));
		m_vertexArray->setIndexBuffer(std::move(indexBuffer));
		m_texture = std::make_unique<Rendurr::Texture>("assets/textures/wall.jpg");
	}

	void EditurrLayer::onAttach()
	{
	}

	void EditurrLayer::onUpdate(float dt)
	{
		Rendurr::Renderer::setViewport(800, 600);

		glm::mat4 viewMatrix = m_cameraController.getViewMatrix();
		glm::mat4 projectionMatrix = m_cameraController.getProjectionMatrix();
		Rendurr::CameraUniform cameraUniform{ viewMatrix, projectionMatrix };
		m_shader->uploadUniformSet(cameraUniform);

		m_texture->bind(0);

		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, { 0.0f, 0.0f, 0.0f });
		transform = glm::rotate(transform, dt, glm::vec3(0.0f, 0.0f, 1.0f));
		Rendurr::MeshUniforms uniform{ transform, 0 };

		m_shader->uploadUniformSet(uniform);
		m_shader->use();

		m_vertexArray->bind();
		Rendurr::Renderer::draw(m_vertexArray.get());
		m_vertexArray->unbind();
	}
}
