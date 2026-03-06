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
			{{-0.5f,-0.5f, 0.5f}, {0,0,1}, {0,0}},
			{{ 0.5f,-0.5f, 0.5f}, {0,0,1}, {1,0}},
			{{ 0.5f, 0.5f, 0.5f}, {0,0,1}, {1,1}},
			{{-0.5f, 0.5f, 0.5f}, {0,0,1}, {0,1}},

			// Back face
			{{ 0.5f,-0.5f,-0.5f}, {0,0,-1}, {0,0}},
			{{-0.5f,-0.5f,-0.5f}, {0,0,-1}, {1,0}},
			{{-0.5f, 0.5f,-0.5f}, {0,0,-1}, {1,1}},
			{{ 0.5f, 0.5f,-0.5f}, {0,0,-1}, {0,1}},

			// Left face
			{{-0.5f,-0.5f,-0.5f}, {-1,0,0}, {0,0}},
			{{-0.5f,-0.5f, 0.5f}, {-1,0,0}, {1,0}},
			{{-0.5f, 0.5f, 0.5f}, {-1,0,0}, {1,1}},
			{{-0.5f, 0.5f,-0.5f}, {-1,0,0}, {0,1}},

			// Right face
			{{ 0.5f,-0.5f, 0.5f}, {1,0,0}, {0,0}},
			{{ 0.5f,-0.5f,-0.5f}, {1,0,0}, {1,0}},
			{{ 0.5f, 0.5f,-0.5f}, {1,0,0}, {1,1}},
			{{ 0.5f, 0.5f, 0.5f}, {1,0,0}, {0,1}},

			// Top face
			{{-0.5f, 0.5f, 0.5f}, {0,1,0}, {0,0}},
			{{ 0.5f, 0.5f, 0.5f}, {0,1,0}, {1,0}},
			{{ 0.5f, 0.5f,-0.5f}, {0,1,0}, {1,1}},
			{{-0.5f, 0.5f,-0.5f}, {0,1,0}, {0,1}},

			// Bottom face
			{{-0.5f,-0.5f,-0.5f}, {0,-1,0}, {0,0}},
			{{ 0.5f,-0.5f,-0.5f}, {0,-1,0}, {1,0}},
			{{ 0.5f,-0.5f, 0.5f}, {0,-1,0}, {1,1}},
			{{-0.5f,-0.5f, 0.5f}, {0,-1,0}, {0,1}},
		};

		std::vector<uint32_t> indices = {
			0, 2, 1, 2, 0, 3,       // Front
			4, 6, 5, 6, 4, 7,       // Back
			8,10, 9,10, 8,11,       // Left
		   12,14,13,14,12,15,       // Right
		   16,18,17,18,16,19,       // Top
		   20,22,21,22,20,23        // Bottom
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
