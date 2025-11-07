#pragma once

#include <Rendurr.hpp>

#include "Render/Texture.hpp"
#include "Render/VertexArray.hpp"
#include "Render/VertexBuffer.hpp"
#include "Scene/Camera.hpp"

namespace Editurr
{
	class EditurrLayer : public Rendurr::Layer
	{
	public:
		EditurrLayer(std::string name);

		void onAttach() override;
		void onUpdate(float dt) override;
	private:
		Rendurr::Camera m_camera;
		std::unique_ptr<Rendurr::Shader> m_shader;
		std::unique_ptr<Rendurr::VertexBuffer> m_vertexBuffer;
		std::unique_ptr<Rendurr::IndexBuffer> m_indexBuffer;
		std::unique_ptr<Rendurr::VertexArray> m_vertexArray;
		std::unique_ptr<Rendurr::Texture> m_texture;
	};
}
