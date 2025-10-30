#include "EditurrLayer.hpp"

#include <iostream>
#include <glad/glad.h>
#include <Render/Renderer.hpp>

namespace Editurr
{
	EditurrLayer::EditurrLayer(std::string name) : Layer(name)
	{
		m_shader = std::make_unique<Rendurr::Shader>("assets/shaders/vertex.glsl", "assets/shaders/frag.glsl");

		std::vector<Rendurr::Vertex> vertices = {
			{{0.5f, 0.5f, 0.0f}},
			{{0.5f, -0.5f, 0.0f}},
			{{-0.5f, -0.5f, 0.0f}},
			{{-0.5f, 0.5f, 0.0f}}
		};
		std::vector<uint32_t> indices{
			0, 1, 3,
			1, 2, 3
		};

		m_vertexBuffer = std::make_unique<Rendurr::VertexBuffer>(vertices);
		m_indexBuffer = std::make_unique<Rendurr::IndexBuffer>(indices);
		m_vertexArray = std::make_unique<Rendurr::VertexArray>();
		m_vertexArray->addVertexBuffer(m_vertexBuffer.get());
		m_vertexArray->setIndexBuffer(std::move(m_indexBuffer));

		GLint vao = 0;
glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vao);

GLint ebo = 0;
glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &ebo);

std::cout << "Current VAO: " << vao << "  EBO: " << ebo << std::endl;

	}

	void EditurrLayer::onAttach()
	{
	}

	void EditurrLayer::onUpdate()
	{
		Rendurr::Renderer::setViewport(800, 600);

		m_shader->use();
		m_vertexArray->bind();
		Rendurr::Renderer::draw(m_vertexArray.get());
		m_vertexArray->unbind();
	}
}
